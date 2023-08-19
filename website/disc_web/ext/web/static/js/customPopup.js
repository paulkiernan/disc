'use strict';

(function ($) {

  $.fn.customPopup = function (ops) {
    const COOKIES = document.cookie;
    const THIS = this;
    const ID = this.attr('id');
    const DEFAULTS = {
      width: '200px',
      top: 0,
      left: 0,
      borderColor: '#999999'
    }
    const SETTINGS = $.extend({}, DEFAULTS, ops);
    let popup_wrap = document.createElement('div');
    let popup_img = document.createElement('div');
    let popup_title = document.createElement('div');
    let popup_btns = document.createElement('div');
    let title_html = `<div class="title-bar"><div class="title-bar-text">Fun Virus!</div><div class="title-bar-controls"> <button class="popup__close" aria-label="Close"></button> </div></div>`
    let img_html = `<img src="${SETTINGS.imgSrc}">`;
    let btns_html = `<section class="field-row" style="justify-content: flex-end"><button type="button" class="popup__close">Sure</button></section>`;

    popup_title.innerHTML = title_html;
    popup_img.innerHTML = img_html;
    popup_btns.innerHTML = btns_html;

    popup_img.classList.add('popup__img');
    popup_btns.classList.add('popup__btns');

    popup_wrap.append(popup_title);
    popup_wrap.append(popup_img);
    popup_wrap.append(popup_btns);


    function setCookies(name, value, expireDays) {
      const TODAY = new Date();
      TODAY.setDate(TODAY.getDate() + expireDays);
      document.cookie = `${name}=${escape(value)}; path=/; expires=${TODAY.toGMTString()};`;
    }

    function checkCookies() {
      if (COOKIES.indexOf(ID + "=done") < 0) {
        // Parse popup
        THIS.append(popup_wrap);

        // add CSS
        $(popup_wrap)
          .addClass("window")
          .css({
            'position': 'fixed',
            'width': SETTINGS.width,
            'top': SETTINGS.top,
            'left': SETTINGS.left,
            'margin': '32px',
          })
          .find('.popup__img img')
          .css({
            'display': 'block',
            'width': '100%',
          })
          .end()
          .find('.popup__btns')
          .find('button')
          .end()
      }
    }

    function init() {
      checkCookies();

      // Event handler
      $(`#${ID} .popup__close`).click(e => {
        THIS.empty();
      })
    }

    init();


    return this;
  };
})(jQuery);
