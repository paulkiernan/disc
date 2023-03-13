FROM alpine:3.7
EXPOSE 80

VOLUME /usr/src/app/public
WORKDIR /usr/src/app

RUN apk add --no-cache \
    build-base \
    python3 \
    python3-dev

COPY . .
RUN pip3 install --no-cache-dir -r requirements.txt

ENV FLASK_ENV=production
CMD ["gunicorn", "--bind", "0.0.0.0:80", "wsgi:application"]
