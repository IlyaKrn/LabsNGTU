import re
import handlers

patterns = [
    (re.compile(r"^(привет|здравствуй|добрый день)$", re.IGNORECASE), handlers.handle_greeting),
    (re.compile(r"^(пока|до свидания)$", re.IGNORECASE), handlers.handle_farewell),
    (re.compile(r"погода в ([а-яА-Яa-zA-Z\- ]+)", re.IGNORECASE), handlers.handle_weather),
    (re.compile(r"(\d+)\s*\+\s*(\d+)"), handlers.handle_addition),
]