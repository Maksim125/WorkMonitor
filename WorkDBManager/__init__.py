import sqlite3
import os
from datetime import datetime
from contextlib import contextmanager

DB_LOC = "\WorkDBManager\database\productivity.db"


@contextmanager
def database_connection(filepath = os.getcwd() + DB_LOC):
    connection = sqlite3.connect(filepath)
    try:
        yield connection
    finally:
        connection.close()

def create(tablename, values):
    with database_connection() as connection:
        cur = connection.cursor()
        cur.execute(f'''CREATE TABLE IF NOT EXISTS {tablename} ({values})''')
        cur.close()

def update(tablename, values):
    with database_connection() as connection:
        cur = connection.cursor()
        cur.execute(f'''INSERT INTO {tablename} VALUES ({values})''')
        connection.commit()
        cur.close()

def read(tablename, qualifier = None):
    with database_connection() as connection:
        cur = connection.cursor()
        if not qualifier:
            data = cur.execute(f"SELECT * FROM {tablename}").fetchall()
        else:
            data = cur.execute(f"SELECT * FROM {tablename} WHERE {qualifier}").fetchall()
        cur.close()
    return data

def delete(tablename, qualifier = None):
    with database_connection() as connection:
        cur = connection.cursor()
        if not qualifier:
            cur.execute(f"DELETE FROM {tablename};")
        else:
            cur.execute(f"DELETE FROM {tablename} WHERE {qualifier};")
        connection.commit()
        cur.close()

if __name__ != "__main__":
    #when importing the DB manager, create the default table that needs to exist for this app
    create(tablename = "productivity", values = "date TEXT, seconds INTEGER")