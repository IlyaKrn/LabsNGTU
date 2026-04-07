import enum
import requests
import spacy
import re
from sklearn.linear_model import LogisticRegression
import logger
import pandas as pd
import joblib
import numpy as np

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