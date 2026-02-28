from datetime import datetime
import sqlite3


def init_db():
    conn = sqlite3.connect("bot.db")
    cursor = conn.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS messages (
            id INTEGER PRIMARY KEY,
            time TEXT,
            message TEXT
        )
    """)

    conn.commit()
    conn.close()

def log_message(user, bot):
    conn = sqlite3.connect("bot.db")
    cursor = conn.cursor()
    cursor.execute("INSERT OR REPLACE INTO messages (time, message) VALUES (?, ?)",
                   (datetime.now(), 'user: ' + user))
    cursor.execute("INSERT OR REPLACE INTO messages (time, message) VALUES (?, ?)",
                   (datetime.now(), 'bot: ' + bot))

    conn.commit()
    conn.close()
