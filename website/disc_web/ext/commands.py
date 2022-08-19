import click

from disc_web.ext.database import db

from disc_web.models import Guestlog


def create_db():
    """Creates database"""
    db.create_all()


def drop_db():
    """Cleans database"""
    db.drop_all()


def populate_db():
    """Populate db with sample data"""
    data = [
        Guestlog(id=1, name="Bonk", content="Fuck yer burn"),
        Guestlog(id=2, name="Meow", content="Hey, that's not nice."),
    ]
    db.session.bulk_save_objects(data)
    db.session.commit()
    return Guestlog.query.all()


def init_app(app):
    # add multiple commands in a bulk
    for command in [create_db, drop_db, populate_db]:
        app.cli.add_command(app.cli.command()(command))
