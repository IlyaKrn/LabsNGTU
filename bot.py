import re
from patterns import patterns
from handlers import get_weather
import logger
import spacy
nlp = spacy.load("ru_core_news_sm")

logger.init_db()

def process_message(message: str):
    print(message)
    doc = nlp(message)
    city = None
    for ent in doc.ents:
        if ent.label_ in ["GPE", "LOC"]:
            city = ent.lemma_
            if "погод" in message and city:
                return get_weather(city)
    message = message.strip()
    for pattern, handler in patterns:
        match = pattern.search(message)
        if match:
            return handler(match)
    return "Я не понимаю запрос."

if __name__ == "__main__":
    while True:
        user_input = input("Вы: ")
        response = process_message(user_input)
        logger.log_message(user_input, response)
        print("Бот:", response)


