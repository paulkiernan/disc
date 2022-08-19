from flask import Blueprint

from .views import index, api_guestbook

bp = Blueprint(
    "webui",
    __name__,
    template_folder="templates",
    static_folder="static",
    static_url_path='/cgi_bin/static',
)

bp.add_url_rule("/", view_func=index)
bp.add_url_rule(
    "/guestbook",
    view_func=api_guestbook,
    methods=["GET", "POST"]
)


def init_app(app):
    app.register_blueprint(bp)
