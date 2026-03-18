import enum
import requests
import spacy
import re

from typer.cli import state

import logger

# анализатор строк
nlp = spacy.load("ru_core_news_sm")

# состояния автомата
class States:
    START = 'START'
    GREETING = 'GREETING'
    GOODBYE = 'GOODBYE'
    ADDITION = 'ADDITION'
    WEATHER = 'WEATHER'
    WEATHER_CITY = 'WEATHER_CITY'
    END = 'END'

# выражения
greeting_regex = re.compile(r"(\A|\s)(здравствуй(те)?|привет|хай|добр(ое\s+утро|ый\s+(день|вечер))|салют|здарова)(\Z|\s)",re.IGNORECASE)
goodbye_regex = re.compile(r"(\A|\s)(досвидания|до\s+свидания|пока|всего\s+(доброго|хорошего)|до\s+(встречи|связи)|счастливо|увидимся)(\Z|\s)",re.IGNORECASE)
addition_regex = re.compile(r"(\A|\s)([\d\s*\+\s*]+\d)(\Z|\s)",re.IGNORECASE)
weather_regex = re.compile(r"(\A|\s)((не|)погод(а|ы|е|у|ой))(\Z|\s)",re.IGNORECASE)
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
                if re.search(greeting_regex, message):
                    state = States.GREETING
                elif re.search(weather_regex, message):
                    state = States.WEATHER
                elif re.search(addition_regex, message):
                    state = States.ADDITION
                elif re.search(goodbye_regex, message):
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