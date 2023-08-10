FROM python:3.11.4-slim
EXPOSE 80

VOLUME /usr/src/app/public
WORKDIR /usr/src/app

COPY requirements.txt .
RUN pip3 install -r requirements.txt

COPY . .

ENV FLASK_ENV=production
CMD ["gunicorn", "--bind", "0.0.0.0:80", "wsgi:application"]
