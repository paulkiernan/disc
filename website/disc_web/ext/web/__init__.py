from flask import Blueprint

from .views import api_guestbook
from .views import guestbook
from .views import index
from .views import egggame
from .views import home
from .views import bait
from .views import api_bait_reservation

bp = Blueprint(
    "webui",
    __name__,
    template_folder="templates",
    static_folder="static",
    static_url_path="/cgi_bin/static",
)

bp.add_url_rule("/", view_func=index)
bp.add_url_rule("/guestbook.html", view_func=guestbook)
bp.add_url_rule("/guestbook", view_func=api_guestbook, methods=["GET", "POST"])
bp.add_url_rule("/egggame.html", view_func=egggame)
bp.add_url_rule("/home.html", view_func=home)
bp.add_url_rule("/bait.html", view_func=bait)
bp.add_url_rule("/bait.html", view_func=api_bait_reservation, methods=["GET", "POST"])


def init_app(app):
    app.register_blueprint(bp)
