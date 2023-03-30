# Поисковой движок search-engine
Искусственный интеллект, разрабатывающийся в целях автоматизации и облегчении повседневных задач. Главное его отличие от конкурентов - это новый режим обучения, который подразумевает под собой обычный разговор. Так голосового ассистента можно научить всему, что ты захочешь

## Содержание
- [Технологии](#технологии)
- [Начало работы](#использование)
- [Unit - Testing](#тесты)

## Технологии
- [C++ 17](https://en.cppreference.com/w/cpp/17)
- [nlohmann_json](https://github.com/nlohmann/json)
- [GTest](https://github.com/google/googletest)

## Использование

Для начала вам потребуется правильно сконфигурировать программу. Для этого в корневом каталоге проекта перейдите в папку _json_ и настройте _config.json_ и _requests.json_

Примерная структура для файла <b>_config.json_</b>:
```json
{
    "config": {
        "name": "search-engine-skillbox",
        "version": "1.0",
        "max_responses": 5
    },

    "files": [
        "/your_absolute/path/file.txt",
        "/your_absolute/path/file1.txt",
        "/your_absolute/path/file2.txt",
        ...
    ]
}
```

<hr>

Примерная структура для файла <b>_requests.json_</b>:
```json
{
    "requests": [
        "moscow is the capital of russia",
        "response more",
        "maximum 1000",
        ...
    ]
}
```

<hr>

Установите необходимые зависимости, и соберите приложение:

```sh
$ cmake CMakeLists.txt && make
```

<hr>

Теперь перейдите в директорию сборки проекта и запустите поисковой движок:
```sh
$ cd bin && ./search-engine-skillbox
```

## Тесты

Чтобы протестировать приложение на корректность вы можете запустить второй бинарный файл:

```sh
cd bin && ./unit-testing
```