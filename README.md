## Домашнее задание

В репозитории приведен код web-приложения, которое сохраняет в БД введенную информацию о задаче - ее имя.

## Часть I. Docker

1. Добавьте в код Dockerfile, который позволит запустить web-приложение с исходным кодом в каталоге app/ через docker.

Клонируем исходный репозиторий с заданием:

```sh
$ git clone https://github.com/tp-lessons/lab_docker.git
```

```
Клонирование в «lab_docker»...
remote: Enumerating objects: 16, done.
remote: Counting objects: 100% (16/16), done.
remote: Compressing objects: 100% (12/12), done.
remote: Total 16 (delta 1), reused 13 (delta 1), pack-reused 0 (from 0)
Получение объектов: 100% (16/16), 5.01 КиБ | 5.01 МиБ/с, готово.
Определение изменений: 100% (1/1), готово.
```

Перемещаемся в папку app и создаем здесь Dockerfile:

```sh
$ nano Dockerfile
```

Здесь будет такой код:

```sh
FROM python:3.9-slim

WORKDIR /app

COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 5000

CMD ["python", "app.py"]
```

Собираем контейнер:

```sh
$ docker build -t my-flask-app .
```

Вывод:

```
[+] Building 53.7s (10/10) FINISHED                                                                      docker:default
 => [internal] load build definition from Dockerfile                                                               0.0s
 => => transferring dockerfile: 199B                                                                               0.0s
 => [internal] load metadata for docker.io/library/python:3.9-slim                                                 9.3s
 => [internal] load .dockerignore                                                                                  0.0s
 => => transferring context: 2B                                                                                    0.0s
 => [internal] load build context                                                                                  0.0s
 => => transferring context: 1.91kB                                                                                0.0s
 => [1/5] FROM docker.io/library/python:3.9-slim@sha256:2d97f6910b16bd338d3060f261f53f144965f755599aab1acda1e13cf  0.0s
 => => resolve docker.io/library/python:3.9-slim@sha256:2d97f6910b16bd338d3060f261f53f144965f755599aab1acda1e13cf  0.0s
 => CACHED [2/5] WORKDIR /app                                                                                      0.0s
 => [3/5] COPY requirements.txt .                                                                                  0.0s
 => [4/5] RUN pip install --no-cache-dir -r requirements.txt                                                      40.7s
 => [5/5] COPY . .                                                                                                 0.0s 
 => exporting to image                                                                                             3.6s 
 => => exporting layers                                                                                            3.0s 
 => => exporting manifest sha256:eb5b356c545ef6fddcf9e606e1318b9d1e932eba7c3ea83ef05d5045b7b4eb33                  0.0s 
 => => exporting config sha256:8a7c0818c898cc5017f014700249aa302c15ddcc85e83100d66a23d0ddc6e9d0                    0.0s 
 => => exporting attestation manifest sha256:bb6050345701a5f0f7e693f32a0f810d18a1770f86e165d5271fd1025debd0c0      0.0s 
 => => exporting manifest list sha256:14e836808ac8c8797736dfbb43f30448c47fb355a7a6dfa73b7e675897ae62d0             0.0s
 => => naming to docker.io/library/my-flask-app:latest                                                             0.0s
 => => unpacking to docker.io/library/my-flask-app:latest
```

2. Выполните запуск контейнера с этим приложением.

Запускаем его:

```sh
$ docker run -d --name my-running-app -p 5000:5000 my-flask-app
```

Вывод (его id):

```sh
c89b1ae42ad15e4c765f858849e5940e0bf3a97b6794e48154f193789ef53ccb
```

Проверяем, что он запустился:

```sh
$ docker ps
```

Вывод:

```sh
CONTAINER ID   IMAGE          COMMAND                  CREATED              STATUS                    PORTS                                                    NAMES
c89b1ae42ad1   my-flask-app   "python app.py"          About a minute ago   Up About a minute         0.0.0.0:5000->5000/tcp, [::]:5000->5000/tcp              my-running-app
```

3. Скопируйте из консоли в каталог /home/ контейнера файл README.md.

```sh
$ echo "Это пример README" > README.md
```

```sh
docker cp README.md my-running-app:/home/
```

Вывод:

```sh
Successfully copied 27B (transferred 2.05kB) to my-running-app:/home/
```

4. Подключитесь к терминалу контейнера с приложением в интерактивном режиме. Проверьте, что скопированный файл находится в нужном каталоге.

```sh
docker exec -it my-running-app bash
```

```sh
root@c89b1ae42ad1:/app# ls /home/
README.md
```

5. Выйдите из интерактивного режима.

```sh
root@c89b1ae42ad1:/app# exit
exit
```

6. Остановите контейнер с приложением.

```sh
$ docker stop my-running-app

$ docker rm my-running-app
```

## Часть II. Docker compose
1. Создайте файл docker-compose.yml таким образом, чтобы совместно с описанным в части 1 контейнером работала бы база данных mysql. Файл инициализации БД в каталоге db/init.sql. Также пропишите порт подключения к приложению. Например 5000.

```sh
$ cat > docker-compose.yml <<'EOF'
services:
  web:
    build: ./app
    ports:
      - "5000:5000"
    environment:
      DB_HOST: db
      DB_USER: user
      DB_PASS: example
      DB_NAME: mydb
    depends_on:
      db:
        condition: service_healthy

  db:
    image: mysql:8.0
    restart: always
    environment:
      MYSQL_ROOT_PASSWORD: rootpassword
      MYSQL_DATABASE: mydb
      MYSQL_USER: user
      MYSQL_PASSWORD: example
    ports:
      - "3306:3306"
    volumes:
      - db_data:/var/lib/mysql
      - ./db/init.sql:/docker-entrypoint-initdb.d/init.sql
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "localhost", "-u", "root", "-prootpassword"]
      interval: 10s
      timeout: 5s
      retries: 5

volumes:
  db_data:
```

2. Запустите связку web-приложение - БД.

```sh
$ docker compose up --build
```

3. Проверьте подключение к приложению через браузер. Сделайте снимок экрана.

Появились проблемы с кодировкой, решил проблему путем перевода из 1252 в UTF-8.

```sh
$ docker exec -it lab_docker-web-1 bash -c "cat > /app/models.py <<'EOF'
import os
import pymysql

class ItemModel:
    def __init__(self):
        self.config = {
            'host': os.getenv('DB_HOST'),
            'user': os.getenv('DB_USER'),
            'password': os.getenv('DB_PASS'),
            'database': os.getenv('DB_NAME'),
            'charset': 'utf8mb4',
            'cursorclass': pymysql.cursors.DictCursor
        }

    def get_all_items(self):
        try:
            conn = pymysql.connect(**self.config)
            cursor = conn.cursor()
            cursor.execute('SELECT name FROM items')
            items = cursor.fetchall()
            cursor.close()
            conn.close()
            fixed = []
            for item in items:
                name = item['name']
                if isinstance(name, str):
                    try:
                        # Перекодировка из cp1252 в utf-8
                        name = name.encode('cp1252').decode('utf-8')
                    except (UnicodeEncodeError, UnicodeDecodeError):
                        pass
                fixed.append({'name': name})
            return fixed
        except Exception as e:
            print(f'Error: {e}')
            return []
EOF"
```

```sh
$ docker compose restart web
```

4. Проверьте работу приложения через браузер.

По ссылке http://localhost:5000 все отображается корректно.
