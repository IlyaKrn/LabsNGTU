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

tokenizer = AutoTokenizer.from_pretrained("DeepPavlov/rubert-base-cased")
model = AutoModel.from_pretrained("DeepPavlov/rubert-base-cased")

def bert_vector(text):
    inputs = tokenizer(text, return_tensors="pt", truncation=True, padding=True)
    outputs = model(**inputs)
    cls_vector = outputs.last_hidden_state[:, 0, :]
    return cls_vector.detach().numpy()[0]

X = np.array([bert_vector(text) for text in texts])
y = labels

clf = LogisticRegression(max_iter=1000)
clf.fit(X, y)

bert_cache = {}

def cached_bert_vector(text):
    if text not in bert_cache:
        bert_cache[text] = bert_vector(text)
    return bert_cache[text]

model = AutoModelForSequenceClassification.from_pretrained("DeepPavlov/rubert-base-cased", num_labels=3)










MODEL_NAME = "DeepPavlov/rubert-base-cased"
tokenizer = AutoTokenizer.from_pretrained(MODEL_NAME)
model = AutoModelForSequenceClassification.from_pretrained(MODEL_NAME,num_labels=3)

df = pd.read_csv("intents.csv")

label2id = {label: idx for idx, label in enumerate(df.intent.unique())}
id2label = {v: k for k, v in label2id.items()}

df["label"] = df.intent.map(label2id)

train_texts, val_texts, train_labels, val_labels = train_test_split(
    df.text.tolist(),df.label.tolist(),test_size=0.2)



def tokenize(texts):
    return tokenizer(
        texts,
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
    num_train_epochs=4,
    per_device_train_batch_size=8,
    per_device_eval_batch_size=8,
    evaluation_strategy="epoch",
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

model = AutoModelForSequenceClassification.from_pretrained("intent_model")
tokenizer = AutoTokenizer.from_pretrained("intent_model")





# bot.py
MODEL_PATH = "intent_model"
tokenizer = AutoTokenizer.from_pretrained(MODEL_PATH)
model = AutoModelForSequenceClassification.from_pretrained(MODEL_PATH)
model.eval()

label_map = {
 0: "weather",
    1: "greeting",
    2: "help"
}

def predict_intent(text: str) -> str:
    inputs = tokenizer(text, return_tensors="pt", truncation=True)
    with torch.no_grad():
        outputs = model(**inputs)
    logits = outputs.logits
    predicted_class = torch.argmax(logits, dim=1).item()
    return label_map[predicted_class]

# nlp_utils.py

nlp = spacy.load("ru_core_news_md")

def extract_city(text: str):
    doc = nlp(text)
    for ent in doc.ents:
        if ent.label_ == "LOC":
            return ent.text
    return None

# bot.py

from nlp_utils import extract_city
from dialog_manager import get_state, set_state
from weather import get_weather
from database import log_message

def handle_message(user_id: int, text: str) -> str:
    log_message(user_id, text)

    state = get_state(user_id)
    intent = predict_intent(text)

    # Если бот ждёт город
    if state == "WAIT_CITY":
        city = text
        weather = get_weather(city)
        set_state(user_id, "START")
        return weather

    # Если определён интент погоды
    if intent == "weather":
        city = extract_city(text)

        if city:
            return get_weather(city)
        else:
            set_state(user_id, "WAIT_CITY")
            return "В каком городе вас интересует погода?"

    elif intent == "greeting":
        return "Здравствуйте!"

    elif intent == "help":
        return "Я могу рассказать погоду. Спросите, например: Какая погода в Москве?"

    return "Я не понял запрос."



# состояния автомата
class States:
    START = 'START'
    GREETING = 'GREETING'
    GOODBYE = 'GOODBYE'
    ADDITION = 'ADDITION'
    WEATHER = 'WEATHER'
    WEATHER_CITY = 'WEATHER_CITY'
    END = 'END'

# intent
intents = [
    'GREETING',
    'GOODBYE',
    'ADDITION',
    'WEATHER',
]

# анализатор строк
nlp = spacy.load("ru_core_news_md")

# нормализация
def preprocess(text):
    tokens = []
    for token in nlp(text):
        if not token.is_stop and not token.is_punct:
            tokens.append(token.lemma_)
    return " ".join(tokens)

# нормализация
def vectorize(text):
    return nlp(text).vector

# датасет
data = pd.read_csv("dataset.csv")
texts = [preprocess(text) for text in data.iloc[:, 0]]
labels = data.iloc[:, 1]

# векторизация
X = np.array([vectorize(text) for text in texts])

# модель
model = LogisticRegression()
model.fit(X, labels)

# получение intent
def intent(text):
    vector = vectorize(text).reshape(1, -1)
    proba = model.predict_proba(vector)
    if max(proba[0]) < 0.3:
        return None
    print(model.predict(vector))
    return model.predict(vector)[0]

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