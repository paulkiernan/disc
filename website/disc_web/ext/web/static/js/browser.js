var cursoreffects=function(t){"use strict";return t.bubbleCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2},c=[],a=[];function A(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function d(t){if(t.touches.length>0)for(let e=0;e<t.touches.length;e++)g(t.touches[e].clientX,t.touches[e].clientY,a[Math.floor(Math.random()*a.length)])}function r(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY;g(s.x,s.y)}function g(t,e,i){c.push(new p(t,e,i))}function u(){!function(){i.clearRect(0,0,h,l);for(let t=0;t<c.length;t++)c[t].update(i);for(let t=c.length-1;t>=0;t--)c[t].lifeSpan<0&&c.splice(t,1)}(),requestAnimationFrame(u)}function p(t,e,i){const n=Math.floor(60*Math.random()+60);this.initialLifeSpan=n,this.lifeSpan=n,this.velocity={x:(Math.random()<.5?-1:1)*(Math.random()/10),y:-1*Math.random()-.4},this.position={x:t,y:e},this.canv=i,this.baseDimension=4,this.update=function(t){this.position.x+=this.velocity.x,this.position.y+=this.velocity.y,this.velocity.x+=2*(Math.random()<.5?-1:1)/75,this.velocity.y-=Math.random()/600,this.lifeSpan--;const e=.2+(this.initialLifeSpan-this.lifeSpan)/this.initialLifeSpan;t.fillStyle="#e6f1f7",t.strokeStyle="#3a92c5",t.beginPath(),t.arc(this.position.x-this.baseDimension/2*e,this.position.y-this.baseDimension/2,this.baseDimension*e,0,2*Math.PI),t.stroke(),t.fill(),t.closePath()}}e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),o.addEventListener("mousemove",r),o.addEventListener("touchmove",d,{passive:!0}),o.addEventListener("touchstart",d,{passive:!0}),window.addEventListener("resize",A),u()},t.clockCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2};const c=t&&t.dateColor||"blue",a=t&&t.faceColor||"black",A=t&&t.secondsColor||"red",d=t&&t.minutesColor||"black",r=t&&t.hoursColor||"black",g=.4;let u=new Date,p=u.getDate(),y=u.getYear()+1900;const f=(" "+["SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"][u.getDay()]+" "+p+" "+["JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"][u.getMonth()]+" "+y).split(""),x=["3","4","5","6","7","8","9","10","11","12","1","2"],m=x.length,w=["•","•","•"],v=["•","•","•","•"],E=["•","•","•","•","•"],C=360/m,M=360/f.length,B=45/6.5,R=[],Y=[],S=[],b=[],L=[],W=[],H=[],I=[],X=[];var D=parseInt(f.length+m+w.length+v.length+E.length)+1;function T(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function P(t){if(t.touches.length>0)if(n){const e=o.getBoundingClientRect();s.x=t.touches[0].clientX-e.left,s.y=t.touches[0].clientY-e.top}else s.x=t.touches[0].clientX,s.y=t.touches[0].clientY}function F(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY}function J(){!function(){S[0]=Math.round(R[0]+=(s.y-R[0])*g),b[0]=Math.round(Y[0]+=(s.x-Y[0])*g);for(let t=1;t<D;t++)S[t]=Math.round(R[t]+=(S[t-1]-R[t])*g),b[t]=Math.round(Y[t]+=(b[t-1]-Y[t])*g),R[t-1]>=l-80&&(R[t-1]=l-80),Y[t-1]>=h-80&&(Y[t-1]=h-80)}(),function(){i.clearRect(0,0,h,l);const t=new Date,e=t.getSeconds(),n=Math.PI*(e-15)/30,o=t.getMinutes(),s=Math.PI*(o-15)/30,c=t.getHours(),a=Math.PI*(c-3)/6+Math.PI*parseInt(t.getMinutes())/360;for(let t=0;t<X.length;t++)X[t].y=R[t]+67.5*Math.sin(-n+t*M*Math.PI/180),X[t].x=Y[t]+67.5*Math.cos(-n+t*M*Math.PI/180),i.fillStyle=X[t].color,i.fillText(X[t].value,X[t].x,X[t].y);for(let t=0;t<I.length;t++)I[t].y=R[X.length+t]+45*Math.sin(t*C*Math.PI/180),I[t].x=Y[X.length+t]+45*Math.cos(t*C*Math.PI/180),i.fillStyle=I[t].color,i.fillText(I[t].value,I[t].x,I[t].y);for(let t=0;t<H.length;t++)H[t].y=R[X.length+m+t]+0+t*B*Math.sin(a),H[t].x=Y[X.length+m+t]+0+t*B*Math.cos(a),i.fillStyle=H[t].color,i.fillText(H[t].value,H[t].x,H[t].y);for(let t=0;t<W.length;t++)W[t].y=R[X.length+m+H.length+t]+0+t*B*Math.sin(s),W[t].x=Y[X.length+m+H.length+t]+0+t*B*Math.cos(s),i.fillStyle=W[t].color,i.fillText(W[t].value,W[t].x,W[t].y);for(let t=0;t<L.length;t++)L[t].y=R[X.length+m+H.length+W.length+t]+0+t*B*Math.sin(n),L[t].x=Y[X.length+m+H.length+W.length+t]+0+t*B*Math.cos(n),i.fillStyle=L[t].color,i.fillText(L[t].value,L[t].x,L[t].y)}(),requestAnimationFrame(J)}!function(t){e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),i.font="10px sans-serif",i.textAlign="center",i.textBaseline="middle";for(let t=0;t<D;t++)R[t]=0,Y[t]=0,S[t]=0,b[t]=0;for(let t=0;t<f.length;t++)X[t]={color:c,value:f[t]};for(let t=0;t<x.length;t++)I[t]={color:a,value:x[t]};for(let t=0;t<w.length;t++)H[t]={color:r,value:w[t]};for(let t=0;t<v.length;t++)W[t]={color:d,value:v[t]};for(let t=0;t<E.length;t++)L[t]={color:A,value:E[t]};o.addEventListener("mousemove",F),o.addEventListener("touchmove",P,{passive:!0}),o.addEventListener("touchstart",P,{passive:!0}),window.addEventListener("resize",T),J()}()},t.emojiCursor=function(t){const e=t&&t.emoji||["😀","😂","😆","😊"];let i=t&&t.element,n=i||document.body,o=window.innerWidth,h=window.innerHeight;const l={x:o/2,y:o/2},s={x:o/2,y:o/2};let c=0;const a=[],A=[];let d,r;function g(t){o=window.innerWidth,h=window.innerHeight,i?(d.width=n.clientWidth,d.height=n.clientHeight):(d.width=o,d.height=h)}function u(t){if(t.touches.length>0)for(let e=0;e<t.touches.length;e++)y(t.touches[e].clientX,t.touches[e].clientY,A[Math.floor(Math.random()*A.length)])}function p(t){t.timeStamp-c<16||window.requestAnimationFrame((()=>{if(i){const e=n.getBoundingClientRect();l.x=t.clientX-e.left,l.y=t.clientY-e.top}else l.x=t.clientX,l.y=t.clientY;Math.hypot(l.x-s.x,l.y-s.y)>1&&(y(l.x,l.y,A[Math.floor(Math.random()*e.length)]),s.x=l.x,s.y=l.y,c=t.timeStamp)}))}function y(t,e,i){a.push(new x(t,e,i))}function f(){!function(){r.clearRect(0,0,o,h);for(let t=0;t<a.length;t++)a[t].update(r);for(let t=a.length-1;t>=0;t--)a[t].lifeSpan<0&&a.splice(t,1)}(),requestAnimationFrame(f)}function x(t,e,i){const n=Math.floor(60*Math.random()+80);this.initialLifeSpan=n,this.lifeSpan=n,this.velocity={x:(Math.random()<.5?-1:1)*(Math.random()/2),y:.4*Math.random()+.8},this.position={x:t,y:e},this.canv=i,this.update=function(t){this.position.x+=this.velocity.x,this.position.y+=this.velocity.y,this.lifeSpan--,this.velocity.y+=.05;const e=Math.max(this.lifeSpan/this.initialLifeSpan,0);t.drawImage(this.canv,this.position.x-this.canv.width/2*e,this.position.y-this.canv.height/2,this.canv.width*e,this.canv.height*e)}}d=document.createElement("canvas"),r=d.getContext("2d"),d.style.top="0px",d.style.left="0px",d.style.pointerEvents="none",i?(d.style.position="absolute",n.appendChild(d),d.width=n.clientWidth,d.height=n.clientHeight):(d.style.position="fixed",document.body.appendChild(d),d.width=o,d.height=h),r.font="21px serif",r.textBaseline="middle",r.textAlign="center",e.forEach((t=>{let e=r.measureText(t),i=document.createElement("canvas"),n=i.getContext("2d");i.width=e.width,i.height=2*e.actualBoundingBoxAscent,n.textAlign="center",n.font="21px serif",n.textBaseline="middle",n.fillText(t,i.width/2,e.actualBoundingBoxAscent),A.push(i)})),n.addEventListener("mousemove",p,{passive:!0}),n.addEventListener("touchmove",u,{passive:!0}),n.addEventListener("touchstart",u,{passive:!0}),window.addEventListener("resize",g),f()},t.fairyDustCursor=function(t){let e=t&&t.colors||["#D61C59","#E7D84B","#1B8798"],i=t&&t.element,n=i||document.body,o=window.innerWidth,h=window.innerHeight;const l={x:o/2,y:o/2},s={x:o/2,y:o/2},c=[],a=[];let A,d;function r(t){o=window.innerWidth,h=window.innerHeight,i?(A.width=n.clientWidth,A.height=n.clientHeight):(A.width=o,A.height=h)}function g(t){if(t.touches.length>0)for(let e=0;e<t.touches.length;e++)p(t.touches[e].clientX,t.touches[e].clientY,a[Math.floor(Math.random()*a.length)])}function u(t){window.requestAnimationFrame((()=>{if(i){const e=n.getBoundingClientRect();l.x=t.clientX-e.left,l.y=t.clientY-e.top}else l.x=t.clientX,l.y=t.clientY;Math.hypot(l.x-s.x,l.y-s.y)>1.5&&(p(l.x,l.y,a[Math.floor(Math.random()*e.length)]),s.x=l.x,s.y=l.y)}))}function p(t,e,i){c.push(new f(t,e,i))}function y(){!function(){d.clearRect(0,0,o,h);for(let t=0;t<c.length;t++)c[t].update(d);for(let t=c.length-1;t>=0;t--)c[t].lifeSpan<0&&c.splice(t,1)}(),requestAnimationFrame(y)}function f(t,e,i){const n=Math.floor(30*Math.random()+60);this.initialLifeSpan=n,this.lifeSpan=n,this.velocity={x:(Math.random()<.5?-1:1)*(Math.random()/2),y:.7*Math.random()+.9},this.position={x:t,y:e},this.canv=i,this.update=function(t){this.position.x+=this.velocity.x,this.position.y+=this.velocity.y,this.lifeSpan--,this.velocity.y+=.02;const e=Math.max(this.lifeSpan/this.initialLifeSpan,0);t.drawImage(this.canv,this.position.x-this.canv.width/2*e,this.position.y-this.canv.height/2,this.canv.width*e,this.canv.height*e)}}A=document.createElement("canvas"),d=A.getContext("2d"),A.style.top="0px",A.style.left="0px",A.style.pointerEvents="none",i?(A.style.position="absolute",n.appendChild(A),A.width=n.clientWidth,A.height=n.clientHeight):(A.style.position="fixed",n.appendChild(A),A.width=o,A.height=h),d.font="21px serif",d.textBaseline="middle",d.textAlign="center",e.forEach((t=>{let e=d.measureText("*"),i=document.createElement("canvas"),n=i.getContext("2d");i.width=e.width,i.height=e.actualBoundingBoxAscent+e.actualBoundingBoxDescent,n.fillStyle=t,n.textAlign="center",n.font="21px serif",n.textBaseline="middle",n.fillText("*",i.width/2,e.actualBoundingBoxAscent),a.push(i)})),n.addEventListener("mousemove",u),n.addEventListener("touchmove",g,{passive:!0}),n.addEventListener("touchstart",g,{passive:!0}),window.addEventListener("resize",r),y()},t.followingDotCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2},c=new function(t,e,i,n){this.position={x:t,y:e},this.width=i,this.lag=n,this.moveTowards=function(t,e,i){this.position.x+=(t-this.position.x)/this.lag,this.position.y+=(e-this.position.y)/this.lag,i.fillStyle="rgba(50, 50, 50, 0.65)",i.beginPath(),i.arc(this.position.x,this.position.y,this.width,0,2*Math.PI),i.fill(),i.closePath()}}(h/2,l/2,10,10);function a(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function A(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY}function d(){i.clearRect(0,0,h,l),c.moveTowards(s.x,s.y,i),requestAnimationFrame(d)}e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),o.addEventListener("mousemove",A),window.addEventListener("resize",a),d()},t.ghostCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2},c=[],a=new Image;function A(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function d(t){if(t.touches.length>0)for(let e=0;e<t.touches.length;e++)g(t.touches[e].clientX,t.touches[e].clientY,a)}function r(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY;g(s.x,s.y,a)}function g(t,e,i){c.push(new p(t,e,i))}function u(){!function(){i.clearRect(0,0,h,l);for(let t=0;t<c.length;t++)c[t].update(i);for(let t=c.length-1;t>=0;t--)c[t].lifeSpan<0&&c.splice(t,1)}(),requestAnimationFrame(u)}function p(t,e,i){this.initialLifeSpan=40,this.lifeSpan=40,this.position={x:t,y:e},this.image=i,this.update=function(t){this.lifeSpan--;const e=Math.max(this.lifeSpan/this.initialLifeSpan,0);t.globalAlpha=e,t.drawImage(this.image,this.position.x,this.position.y)}}a.src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAATCAYAAACk9eypAAAAAXNSR0IArs4c6QAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAhGVYSWZNTQAqAAAACAAFARIAAwAAAAEAAQAAARoABQAAAAEAAABKARsABQAAAAEAAABSASgAAwAAAAEAAgAAh2kABAAAAAEAAABaAAAAAAAAAEgAAAABAAAASAAAAAEAA6ABAAMAAAABAAEAAKACAAQAAAABAAAADKADAAQAAAABAAAAEwAAAAAChpcNAAAACXBIWXMAAAsTAAALEwEAmpwYAAABWWlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iWE1QIENvcmUgNS40LjAiPgogICA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPgogICAgICA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIgogICAgICAgICAgICB4bWxuczp0aWZmPSJodHRwOi8vbnMuYWRvYmUuY29tL3RpZmYvMS4wLyI+CiAgICAgICAgIDx0aWZmOk9yaWVudGF0aW9uPjE8L3RpZmY6T3JpZW50YXRpb24+CiAgICAgIDwvcmRmOkRlc2NyaXB0aW9uPgogICA8L3JkZjpSREY+CjwveDp4bXBtZXRhPgpMwidZAAABqElEQVQoFY3SPUvDQBgH8BREpRHExYiDgmLFl6WC+AYmWeyLg4i7buJX8DMpOujgyxGvUYeCgzhUQUSKKLUS0+ZyptXh8Z5Ti621ekPyJHl+uftfomhaf9Ei5JyxXKfynyEA6EYcLHpwyflT958GAQ7DTABNHd8EbtDbEH2BD5QEQmi2mM8P/Iq+A0SzszEg+3sPjDnDdVEtQKQbMUidHD3xVzf6A9UDEmEm+8h9KTqTVUjT+vB53aHrCbAPiceYq1dQI1Aqv4EhMll0jzv+Y0yiRgCnLRSYyDQHVoqUXe4uKL9l+L7GXC4vkMhE6eW/AOJs9k583ORDUyXMZ8F5SVHVVnllmPNKSFagAJ5DofaqGXw/gHBYg51dIldkmknY3tguv3jOtHR4+MqAzaraJXbEhqHhcQlwGSOi5pytVQHZLN5s0WNe8HPrLYlFsO20RPHkImxsbmHdLJFI76th7Z4SeuF53hTeFLvhRCJRCTKZKxgdnRDbW+iozFJbBMw14/ElwGYc0egMBMFzT21f5Rog33Z7dX02GBm7WV5ZfT5Nn5bE3zuCDe9UxdTpNvK+5AAAAABJRU5ErkJggg==",e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),o.addEventListener("mousemove",r),o.addEventListener("touchmove",d,{passive:!0}),o.addEventListener("touchstart",d,{passive:!0}),window.addEventListener("resize",A),u()},t.rainbowCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2},c=[];const a=t?.length||20,A=t?.colors||["#FE0000","#FD8C00","#FFE500","#119F0B","#0644B3","#C22EDC"],d=t.size||3;let r=!1;function g(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function u(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY;if(!1===r){r=!0;for(let t=0;t<a;t++)e=s.x,i=s.y,void 0,c.push(new y(e,i))}var e,i}function p(){!function(){i.clearRect(0,0,h,l),i.lineJoin="round";let t=[],e=s.x,n=s.y;c.forEach((function(i,o,h){let l=h[o+1]||h[0];i.position.x=e,i.position.y=n,t.push({x:e,y:n}),e+=.4*(l.position.x-i.position.x),n+=.4*(l.position.y-i.position.y)})),A.forEach(((e,n)=>{i.beginPath(),i.strokeStyle=e,t.length&&i.moveTo(t[0].x,t[0].y+n*(d-1)),t.forEach(((t,e)=>{0!==e&&i.lineTo(t.x,t.y+n*d)})),i.lineWidth=d,i.lineCap="round",i.stroke()}))}(),requestAnimationFrame(p)}function y(t,e){this.position={x:t,y:e}}e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),o.addEventListener("mousemove",u),window.addEventListener("resize",g),p()},t.snowflakeCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=["❄️"],l=window.innerWidth,s=window.innerHeight,c={x:l/2,y:l/2},a=[],A=[];function d(t){l=window.innerWidth,s=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=l,e.height=s)}function r(t){if(t.touches.length>0)for(let e=0;e<t.touches.length;e++)u(t.touches[e].clientX,t.touches[e].clientY,A[Math.floor(Math.random()*A.length)])}function g(t){if(n){const e=o.getBoundingClientRect();c.x=t.clientX-e.left,c.y=t.clientY-e.top}else c.x=t.clientX,c.y=t.clientY;u(c.x,c.y,A[Math.floor(Math.random()*h.length)])}function u(t,e,i){a.push(new y(t,e,i))}function p(){!function(){i.clearRect(0,0,l,s);for(let t=0;t<a.length;t++)a[t].update(i);for(let t=a.length-1;t>=0;t--)a[t].lifeSpan<0&&a.splice(t,1)}(),requestAnimationFrame(p)}function y(t,e,i){const n=Math.floor(60*Math.random()+80);this.initialLifeSpan=n,this.lifeSpan=n,this.velocity={x:(Math.random()<.5?-1:1)*(Math.random()/2),y:1+Math.random()},this.position={x:t,y:e},this.canv=i,this.update=function(t){this.position.x+=this.velocity.x,this.position.y+=this.velocity.y,this.lifeSpan--,this.velocity.x+=2*(Math.random()<.5?-1:1)/75,this.velocity.y-=Math.random()/300;const e=Math.max(this.lifeSpan/this.initialLifeSpan,0),i=.0174533*(2*this.lifeSpan);t.translate(this.position.x,this.position.y),t.rotate(i),t.drawImage(this.canv,-this.canv.width/2*e,-this.canv.height/2,this.canv.width*e,this.canv.height*e),t.rotate(-i),t.translate(-this.position.x,-this.position.y)}}e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=l,e.height=s),i.font="12px serif",i.textBaseline="middle",i.textAlign="center",h.forEach((t=>{let e=i.measureText(t),n=document.createElement("canvas"),o=n.getContext("2d");n.width=e.width,n.height=2*e.actualBoundingBoxAscent,o.textAlign="center",o.font="12px serif",o.textBaseline="middle",o.fillText(t,n.width/2,e.actualBoundingBoxAscent),A.push(n)})),o.addEventListener("mousemove",g),o.addEventListener("touchmove",r,{passive:!0}),o.addEventListener("touchstart",r,{passive:!0}),window.addEventListener("resize",d),p()},t.springyEmojiCursor=function(t){let e,i,n,o=t&&t.emoji||"🤪",h=t&&t.element,l=h||document.body,s=window.innerWidth,c=window.innerHeight,a={x:s/2,y:s/2},A=[];function d(t){s=window.innerWidth,c=window.innerHeight,h?(e.width=l.clientWidth,e.height=l.clientHeight):(e.width=s,e.height=c)}function r(t){if(t.touches.length>0)if(h){const e=l.getBoundingClientRect();a.x=t.touches[0].clientX-e.left,a.y=t.touches[0].clientY-e.top}else a.x=t.touches[0].clientX,a.y=t.touches[0].clientY}function g(t){if(h){const e=l.getBoundingClientRect();a.x=t.clientX-e.left,a.y=t.clientY-e.top}else a.x=t.clientX,a.y=t.clientY}function u(){!function(){e.width=e.width,A[0].position.x=a.x,A[0].position.y=a.y;for(let t=1;t<7;t++){let n=new p(0,0);t>0&&y(t-1,t,n),t<6&&y(t+1,t,n);let o,h,l=new p(10*-A[t].velocity.x,10*-A[t].velocity.y),s=new p((n.X+l.X)/1,(n.Y+l.Y)/1+50);A[t].velocity.x+=.01*s.X,A[t].velocity.y+=.01*s.Y,Math.abs(A[t].velocity.x)<.1&&Math.abs(A[t].velocity.y)<.1&&Math.abs(s.X)<.1&&Math.abs(s.Y)<.1&&(A[t].velocity.x=0,A[t].velocity.y=0),A[t].position.x+=A[t].velocity.x,A[t].position.y+=A[t].velocity.y,o=e.clientHeight,h=e.clientWidth,A[t].position.y>=o-11-1&&(A[t].velocity.y>0&&(A[t].velocity.y=.7*-A[t].velocity.y),A[t].position.y=o-11-1),A[t].position.x>=h-11&&(A[t].velocity.x>0&&(A[t].velocity.x=.7*-A[t].velocity.x),A[t].position.x=h-11-1),A[t].position.x<0&&(A[t].velocity.x<0&&(A[t].velocity.x=.7*-A[t].velocity.x),A[t].position.x=0),A[t].draw(i)}}(),requestAnimationFrame(u)}function p(t,e){this.X=t,this.Y=e}function y(t,e,i){let n=A[t].position.x-A[e].position.x,o=A[t].position.y-A[e].position.y,h=Math.sqrt(n*n+o*o);if(h>10){let t=10*(h-10);i.X+=n/h*t,i.Y+=o/h*t}}function f(t){this.position={x:a.x,y:a.y},this.velocity={x:0,y:0},this.canv=t,this.draw=function(t){t.drawImage(this.canv,this.position.x-this.canv.width/2,this.position.y-this.canv.height/2,this.canv.width,this.canv.height)}}!function(){e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",h?(e.style.position="absolute",l.appendChild(e),e.width=l.clientWidth,e.height=l.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=s,e.height=c),i.font="16px serif",i.textBaseline="middle",i.textAlign="center";let t=i.measureText(o),a=document.createElement("canvas"),p=a.getContext("2d");a.width=t.width,a.height=2*t.actualBoundingBoxAscent,p.textAlign="center",p.font="16px serif",p.textBaseline="middle",p.fillText(o,a.width/2,t.actualBoundingBoxAscent),n=a;let y=0;for(y=0;y<7;y++)A[y]=new f(n);l.addEventListener("mousemove",g),l.addEventListener("touchmove",r,{passive:!0}),l.addEventListener("touchstart",r,{passive:!0}),window.addEventListener("resize",d),u()}()},t.trailingCursor=function(t){let e,i,n=t&&t.element,o=n||document.body,h=window.innerWidth,l=window.innerHeight,s={x:h/2,y:h/2},c=[];const a=t.particles||15;let A=!1,d=new Image;function r(t){h=window.innerWidth,l=window.innerHeight,n?(e.width=o.clientWidth,e.height=o.clientHeight):(e.width=h,e.height=l)}function g(t){if(n){const e=o.getBoundingClientRect();s.x=t.clientX-e.left,s.y=t.clientY-e.top}else s.x=t.clientX,s.y=t.clientY;if(!1===A){A=!0;for(let t=0;t<a;t++)e=s.x,i=s.y,h=d,c.push(new p(e,i,h))}var e,i,h}function u(){!function(){i.clearRect(0,0,h,l);let t=s.x,e=s.y;c.forEach((function(n,o,h){let l=h[o+1]||h[0];n.position.x=t,n.position.y=e,n.move(i),t+=.4*(l.position.x-n.position.x),e+=.4*(l.position.y-n.position.y)}))}(),requestAnimationFrame(u)}function p(t,e,i){this.position={x:t,y:e},this.image=i,this.move=function(t){t.drawImage(this.image,this.position.x,this.position.y)}}d.src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAwAAAATCAYAAACk9eypAAAAAXNSR0IArs4c6QAAACBjSFJNAAB6JgAAgIQAAPoAAACA6AAAdTAAAOpgAAA6mAAAF3CculE8AAAAhGVYSWZNTQAqAAAACAAFARIAAwAAAAEAAQAAARoABQAAAAEAAABKARsABQAAAAEAAABSASgAAwAAAAEAAgAAh2kABAAAAAEAAABaAAAAAAAAAEgAAAABAAAASAAAAAEAA6ABAAMAAAABAAEAAKACAAQAAAABAAAADKADAAQAAAABAAAAEwAAAAAChpcNAAAACXBIWXMAAAsTAAALEwEAmpwYAAABWWlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iWE1QIENvcmUgNS40LjAiPgogICA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPgogICAgICA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIgogICAgICAgICAgICB4bWxuczp0aWZmPSJodHRwOi8vbnMuYWRvYmUuY29tL3RpZmYvMS4wLyI+CiAgICAgICAgIDx0aWZmOk9yaWVudGF0aW9uPjE8L3RpZmY6T3JpZW50YXRpb24+CiAgICAgIDwvcmRmOkRlc2NyaXB0aW9uPgogICA8L3JkZjpSREY+CjwveDp4bXBtZXRhPgpMwidZAAABqElEQVQoFY3SPUvDQBgH8BREpRHExYiDgmLFl6WC+AYmWeyLg4i7buJX8DMpOujgyxGvUYeCgzhUQUSKKLUS0+ZyptXh8Z5Ti621ekPyJHl+uftfomhaf9Ei5JyxXKfynyEA6EYcLHpwyflT958GAQ7DTABNHd8EbtDbEH2BD5QEQmi2mM8P/Iq+A0SzszEg+3sPjDnDdVEtQKQbMUidHD3xVzf6A9UDEmEm+8h9KTqTVUjT+vB53aHrCbAPiceYq1dQI1Aqv4EhMll0jzv+Y0yiRgCnLRSYyDQHVoqUXe4uKL9l+L7GXC4vkMhE6eW/AOJs9k583ORDUyXMZ8F5SVHVVnllmPNKSFagAJ5DofaqGXw/gHBYg51dIldkmknY3tguv3jOtHR4+MqAzaraJXbEhqHhcQlwGSOi5pytVQHZLN5s0WNe8HPrLYlFsO20RPHkImxsbmHdLJFI76th7Z4SeuF53hTeFLvhRCJRCTKZKxgdnRDbW+iozFJbBMw14/ElwGYc0egMBMFzT21f5Rog33Z7dX02GBm7WV5ZfT5Nn5bE3zuCDe9UxdTpNvK+5AAAAABJRU5ErkJggg==",e=document.createElement("canvas"),i=e.getContext("2d"),e.style.top="0px",e.style.left="0px",e.style.pointerEvents="none",n?(e.style.position="absolute",o.appendChild(e),e.width=o.clientWidth,e.height=o.clientHeight):(e.style.position="fixed",document.body.appendChild(e),e.width=h,e.height=l),o.addEventListener("mousemove",g),window.addEventListener("resize",r),u()},Object.defineProperty(t,"__esModule",{value:!0}),t}({});
