from flask import Flask, request
import sqlite3
from datetime import datetime

app = Flask(__name__)

@app.route('/temperature', methods=['POST'])
def temperature():
    data = request.get_json()
    temp = data.get('temperature')
    conn = sqlite3.connect('data.db')
    c = conn.cursor()
    c.execute("INSERT INTO temperature VALUES (?, ?)", (datetime.now(), temp))
    conn.commit()
    conn.close()
    return "OK", 200

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000)
