import re
from patterns import patterns
import logger

logger.init_db()

def process_message(message: str):
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


