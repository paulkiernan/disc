from functools import wraps

from flask import redirect
from flask import render_template
from flask import request

from disc_web.ext.database import db
from disc_web.models import Guestlog
from disc_web.models import Reservation
from disc_web.models import ReservationChangelog
from disc_web.models import ViewCount


def increment_view_count(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        c = ViewCount.query.first()
        c.counter += 1
        db.session.add(c)
        db.session.commit()
        return f(*args, **kwargs)

    return decorated_function


@increment_view_count
def index():
    return render_template("index.html")


@increment_view_count
def guestbook():
    logs = Guestlog.query.order_by(Guestlog.time_created.desc()).all()
    return render_template("guestbook.html", logs=logs)


@increment_view_count
def api_guestbook():
    log = Guestlog(name=request.form["author"], content=request.form["content"])
    db.session.add(log)
    db.session.commit()
    return redirect("/guestbook.html")


@increment_view_count
def egggame():
    return render_template("egggame.html")


@increment_view_count
def home():
    counter = ViewCount.query.first()
    return render_template("home.html", counter=counter.counter)


@increment_view_count
def bait():
    reservation = Reservation.query.one()
    return render_template("bait.html", reservation=reservation)


@increment_view_count
def api_bait_reservation():
    content = request.form["editordata"]

    changelog = ReservationChangelog(content=content)
    db.session.add(changelog)

    reservation = Reservation.query.one()
    reservation.content = content
    db.session.add(reservation)

    db.session.commit()

    return redirect("/bait.html")


@increment_view_count
def wipeout():
    return render_template("wipeout.html")
