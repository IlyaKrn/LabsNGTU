import sqlite3

def init():
    db = sqlite3.connect("bot.db")
    db.cursor().execute('CREATE TABLE IF NOT EXISTS messages (' +
            'id                         INTEGER PRIMARY KEY,' +
            'timestamp                  TEXT DEFAULT (DATETIME(\'now\', \'localtime\')),' +
            'author                     TEXT' +
            'message                    TEXT' +
    ')')
    db.commit()
    db.close()

def log(author, message):
    db = sqlite3.connect("bot.db")
    db.cursor().execute("INSERT INTO messages (author, message) VALUES (?, ?);", [author, message])
    db.commit()
    db.close()
