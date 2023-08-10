from flask import abort
from flask import redirect
from flask import render_template
from flask import request

from disc_web.models import Guestlog
from disc_web.ext.database import db


def index():
    return render_template('index.html')


def guestbook():
    logs = Guestlog.query.order_by(Guestlog.time_created.desc()).all()
    return render_template('guestbook.html', logs=logs)


def api_guestbook():
    log = Guestlog(
        name=request.form['author'],
        content=request.form['content']
    )
    db.session.add(log)
    db.session.commit()
    return redirect('/guestbook.html')

def egggame():
    return render_template('egggame.html')

def home():
    return render_template('home.html')
