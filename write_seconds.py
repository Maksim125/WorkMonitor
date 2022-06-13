import sys
import datetime as dt
import pandas as pd
from win10toast import ToastNotifier
import os
from WorkDBManager import create, read, update, delete


ICON_PATH = "\images\desk.ico"


def main():
    seconds = sys.argv[1]
    if seconds.isnumeric(): #Argument is to write the number of seconds passed
        update(tablename = "productivity", values = f"'{str(dt.datetime.now())}', {seconds}")
        show_toast()
    else: #Argument is to notify an hour passed
        notify_hour()

def notify_hour():
    toaster = ToastNotifier()
    message = "One hour has just passed!"
    toaster.show_toast("Productivity", message, duration = 5, threaded = True, icon_path = os.getcwd()+ICON_PATH)

def show_toast():
    toaster = ToastNotifier()
    now = dt.datetime.now()
    now_stripped = dt.datetime(year =now.year, month = now.month, day = now.day)
    earliest, latest = now_stripped - dt.timedelta(days = 5), now_stripped + dt.timedelta(days = 1)
    qualifier = f"date BETWEEN '{earliest}' AND '{latest}'"
    data = read("productivity", qualifier= qualifier)
    df = pd.DataFrame(data, columns = ["date", "seconds"]).set_index("date")
    df.index = pd.to_datetime(df.index)
    seconds_per_day = df.resample("D").seconds.sum()
    
    display_dates = 3
    last_3_days = list(zip(seconds_per_day.index[-display_dates:], seconds_per_day.iloc[-display_dates:]))
    last_3_days.reverse()

    message = ""
    for date, seconds in last_3_days:
        message += f"{date.strftime('%a %b %d')}: {str(dt.timedelta(seconds = seconds))}\n"

    toaster.show_toast("Productivity", message, duration = 5, threaded = True, icon_path = os.getcwd()+ICON_PATH)

if __name__ == "__main__":
    main()