import requests
import json

token = input("вставь свой токен pandascore: ")
url = f"https://api.pandascore.co/csgo/matches?token={token}&per_page=100"

print("качаю матчи...")
response = requests.get(url)
if response.status_code == 200:
    with open("database.json", "w") as f:
        json.dump(response.json(), f)
    print("готово! файл database.json создан.")
else:
    print("ошибка: проверь токен.")