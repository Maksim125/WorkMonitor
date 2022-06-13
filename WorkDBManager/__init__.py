import sqlite3
import os
from datetime import datetime

DB_LOC = "\WorkDBManager\database\productivity.db"

def create(tablename, values):
    connection = sqlite3.connect(os.getcwd() + DB_LOC)
    cur = connection.cursor()
    cur.execute(f'''CREATE TABLE IF NOT EXISTS {tablename} ({values})''')
    connection.close()

def update(tablename, values):
    connection = sqlite3.connect(os.getcwd() + DB_LOC)
    cur = connection.cursor()
    cur.execute(f'''INSERT INTO {tablename} VALUES ({values})''')
    connection.commit()
    connection.close()

def read(tablename, qualifier = None):
    connection = sqlite3.connect(os.getcwd() + DB_LOC)
    cur = connection.cursor()
    if not qualifier:
        data = cur.execute(f"SELECT * FROM {tablename}").fetchall()
    else:
        data = cur.execute(f"SELECT * FROM {tablename} WHERE {qualifier}").fetchall()
    connection.close()
    return data

def delete(tablename, qualifier = None):
    connection = sqlite3.connect(os.getcwd() + DB_LOC)
    cur = connection.cursor()
    if not qualifier:
        cur.execute(f"DELETE FROM {tablename};")
    else:
        cur.execute(f"DELETE FROM {tablename} WHERE {qualifier};")
    connection.commit()
    connection.close()

if __name__ != "__main__":
    create(tablename = "productivity", values = "date TEXT, seconds INTEGER")