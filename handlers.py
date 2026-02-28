import re
import requests

def get_weather(city):
    response = requests.get(f"http://api.weatherstack.com/current?access_key=5a12d3bd1af85af362a71a708768fdf4&query={city}")

    if response.status_code != 200:
        return "Не удалось получить данные о погоде."
    data = response.json()

    return f"Погода в городе {city}:\nТемпература: {data['current']['temperature']}°C\nОписание: {data['current']['weather_descriptions'][0]}\nСкорость ветра: {data['current']['wind_speed']} м/с"


def handle_greeting(match):
    return "Здравствуйте! Чем могу помочь?"

def handle_farewell(match):
    return "До свидания!"

def handle_weather(match):
    city = match.group(1)
    return get_weather(city)

def handle_addition(match):
    a = float(match.group(1))
    b = float(match.group(2))
    return f"Результат: {a + b}"
