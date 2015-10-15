var c = document.getElementById("cube").getContext('2d'),
    w = c.canvas.width,// = window.innerWidth,
    h = c.canvas.height,// = window.innerHeight,
    centerX = w / 2,
    centerY = h / 2;

var dimension = 5,
    mx = 0,
    my = 0,
    zoom = -40;

function move(e) {
    mx = e.pageX / 99;
    my = e.pageY / 99;   
}

function wheelzoom(e) {
    //e.preventDefault();
    zoom = zoom + e.wheelDelta/120;
    if (zoom < -181) zoom = -181;
    if (zoom > -10) zoom = -10;
}

function circle(x, y, r, color) {
    c.fillStyle = color;
    c.beginPath();
    c.arc(x, y, r, 2*Math.PI, false);
    c.fill();
}

randCol = 'rgba(0, 174, 255, ';
if (Math.random()>0.5) randCol = 'rgba(255, 102, 0, ';
    
function draw() {
    c.clearRect(0, 0, c.canvas.width, c.canvas.height);
    for (x = -dimension; x <= dimension; x += 1)
    for (y = -dimension; y <= dimension; y += 1)
    for (z = -dimension; z <= dimension; z += 1) {
   
        // z rotation
        u = x * Math.cos(mx) - y * Math.sin(mx);
        v = x * Math.sin(mx) + y * Math.cos(mx);
        w = z;
        
        // x rotation
        v2 = v * Math.cos(my) - w * Math.sin(my);
        w = v * Math.sin(my) + w * Math.cos(my);
        v = v2;
        
        // y automatic rotation
        rt = Math.sin(Date.now()/1000);
        u2 = u * Math.cos(rt) + w * Math.sin(rt); 
        w = w * Math.cos(rt) - u2 * Math.sin(rt);
        u = u2;     
        
        w = w - zoom;
        if(w<-2)continue;
        
        // transform
        left = centerX +  u / (w + 10) * 650 ;
        top2 = centerY +  v / (w + 10) * 650 ;
       
        radius = 10/(w + 5) | 0 + 'px';
        if (radius<1)radius=1;

        // color illusion based on depth
        opacity = Math.sin(Date.now() / (500+100*(Math.abs(z)+Math.abs(x)+Math.abs(y))/3));
        color = randCol  + opacity + ')';                


        circle(left, top2, radius, color);
        
    }

}

window.addEventListener('mousemove', move, false);
window.addEventListener('mousewheel', wheelzoom, false);   
setInterval(draw, 40);