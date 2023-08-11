from sqlalchemy.sql import func

from disc_web.ext.database import db

class Guestlog(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(255))
    content = db.Column(db.Text)

    time_created = db.Column(db.DateTime(timezone=False), server_default=func.now())
    time_updated = db.Column(db.DateTime(timezone=False), onupdate=func.now())

class Reservation(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    content = db.Column(db.Text)

    time_created = db.Column(db.DateTime(timezone=False), server_default=func.now())
    time_updated = db.Column(db.DateTime(timezone=False), onupdate=func.now())
