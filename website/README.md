# Disconnect Web

Putting the Disco back in "Disconnect from Reality"

## Setting up

```bash
pyenv virtualenv 3.11.4 disc
pyenv activate disc

pip install poetry
poetry install

poetry run gunicorn --bind 0.0.0.0:8080 "wsgi:application"
```

## Exporting requirements

```bash
poetry export -f requirements.txt --output requirements.txt
```
