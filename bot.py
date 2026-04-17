import enum
import requests
import spacy
import re
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
import logger
import pandas as pd
import joblib
import numpy as np
import torch
from transformers import AutoTokenizer, AutoModel
from transformers import AutoModelForSequenceClassification
from transformers import Trainer, TrainingArguments
from datetime import datetime

nlp = spacy.load("ru_core_news_md")

# нормализация
def preprocess(text):
    tokens = []
    for token in nlp(text):
        if not token.is_stop and not token.is_punct:
            tokens.append(token.lemma_)
    return " ".join(tokens)

def train_bert_classifier():
    MODEL_NAME = "DeepPavlov/rubert-base-cased"

    df = pd.read_csv("dataset.csv")
    label2id = {label: idx for idx, label in enumerate(df["intent"].unique())}
    id2label = {v: k for k, v in label2id.items()}
    df["label"] = df["intent"].map(label2id)

    tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME,num_labels=5)

    train_texts, val_texts, train_labels, val_labels = train_test_split(
        df["text"].tolist(), df["label"].tolist(), test_size=0.2)

    def tokenize(texts):
        return tokenizer(texts,
            padding=True,
            truncation=True,
            return_tensors="pt"
        )
    train_encodings = tokenize(train_texts)
    val_encodings = tokenize(val_texts)

    class IntentDataset(torch.utils.data.Dataset):
        def __init__(self, encodings, labels):
            self.encodings = encodings
            self.labels = labels

        def __getitem__(self, idx):
            item = {key: val[idx] for key, val in self.encodings.items()}
            item["labels"] = torch.tensor(self.labels[idx])
            return item

        def __len__(self):
            return len(self.labels)

    train_dataset = IntentDataset(train_encodings, train_labels)
    val_dataset = IntentDataset(val_encodings, val_labels)

    training_args = TrainingArguments(
        output_dir="./results",
        num_train_epochs=35,
        per_device_train_batch_size=8,
        per_device_eval_batch_size=8,
        eval_strategy="epoch",
        logging_dir="./logs",
        learning_rate=2e-5,
    )

    trainer = Trainer(
        model=model,
        args=training_args,
        train_dataset=train_dataset,
        eval_dataset=val_dataset,
    )

    trainer.train()

    def predict_intent(text):
        inputs = tokenizer(text, return_tensors="pt", truncation=True)
        outputs = model(**inputs)
        logits = outputs.logits
        predicted_class = torch.argmax(logits, dim=1).item()
        return id2label[predicted_class]

    model.save_pretrained("intent_model")
    tokenizer.save_pretrained("intent_model")

    return predict_intent





def load_bert_bot():
    MODEL_PATH = "intent_model"
    tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH)
    model = AutoModelForSequenceClassification.from_pretrained(MODEL_PATH)
    model.eval()

    label_map = {
        0: "GREETING",
        1: "GOODBYE",
        2: "WEATHER",
        3: "DATE",
        4: "SMALL_TALK"
    }

    def predict_intent(text: str) -> str:
        inputs = tokenizer(text, return_tensors="pt", truncation=True)
        with torch.no_grad():
            outputs = model(**inputs)
        logits = outputs.logits
        predicted_class = torch.argmax(logits, dim=1).item()
        return label_map[predicted_class]

    return predict_intent

# состояния автомата
class States:
    START = 'START'
    ADDITION = 'ADDITION'
    WEATHER_CITY = 'WEATHER_CITY'
    END = 'END'
    GREETING = 'GREETING'
    GOODBYE = 'GOODBYE'
    WEATHER = 'WEATHER'
    DATE = 'DATE'
    SMALL_TALK = 'SMALL_TALK'

# выражения
addition_regex = re.compile(r"(\A|\s)([\d\s*\+\s*]+\d)(\Z|\s)",re.IGNORECASE)
def getCity(text):return (list(map(lambda ent: ent.lemma_, list(filter(lambda ent: ent.label_ in ["GPE", "LOC"], nlp(text).ents))))+['NULL'])[0]

# апи
def get_weather(city):
    response = requests.get(f"http://api.weatherstack.com/current?access_key=5a12d3bd1af85af362a71a708768fdf4&query={city}")
    if response.status_code != 200:
        return f"Не удалось получить данные о погоде в городе {city}"
    data = response.json()
    return f"Погода в городе {city}:\nТемпература: {data['current']['temperature']}°C\nОписание: {data['current']['weather_descriptions'][0]}\nСкорость ветра: {data['current']['wind_speed']} м/с"

if __name__ == "__main__":
    logger.init()
    lastStates = []
    state = States.START
    message = ''
    # train_bert_classifier()
    intent = load_bert_bot()
    while state != States.END:
        lastStates.append(state)
        match state:
            case 'START':
                message = input('Вы: ')
                i = intent(message)
                if i == 'GREETING':
                    state = States.GREETING
                elif i == 'WEATHER':
                    state = States.WEATHER
                elif i == 'ADDITION':
                    state = States.ADDITION
                elif i == 'GOODBYE':
                    state = States.GOODBYE
                else:
                    print('Извините, я не понял ваше сообщение')
                    state = States.START
                continue

            case States.GREETING:
                print('Привет еще раз!' if States.GREETING in lastStates[0:-1] else 'Привет!')
                state = States.START
                continue

            case States.GOODBYE:
                print('Пока!')
                state = States.END
                continue

            case States.ADDITION:
                print(re.search(addition_regex, message).group().replace(' ', '') + ' = ' + str(sum(int(num) for num in re.findall(r'\d+', re.search(addition_regex, message).group()))))
                state = States.START
                continue

            case States.WEATHER:
                city = getCity(message)
                if city == 'NULL':
                    state = States.WEATHER_CITY
                else:
                    print(get_weather(city))
                    state = States.START
                continue

            case States.WEATHER_CITY:
                message = input('Введите город: ')
                city = getCity(message)
                if city == 'NULL':
                    print('Извините, я не понял ваше сообщение')
                    state = States.START
                else:
                    state = States.WEATHER
                continue
            case States.DATE:
                print(datetime.now().strftime('%d.%m.%Y'))
                continue
            case States.SMALL_TALK:
                print('Спроси что-нибудь другое')
                continue