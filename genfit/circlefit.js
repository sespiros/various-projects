var c = document.getElementById('screen');
var w = c.width = window.innerWidth, h = c.height;
var ctx = c.getContext('2d');

// bootstrap prng
var M = new MersenneTwister();

var smoothstep = function(x) {
    return x*x*(3-2*x);
};

var Circle = function(spec) {
    this.x = (typeof spec.x !== 'undefined') ? spec.x : M.random() * w;
    this.y = (typeof spec.y !== 'undefined') ? spec.y : M.random() * h;
    this.radius = spec.radius || 1;
};

Circle.prototype.intersects = function(circle) {
    var dx = this.x - circle.x;
    var dy = this.y - circle.y;
    var dist = Math.sqrt(dx * dx + dy * dy);

    return dist < this.radius + circle.radius;
};

Circle.prototype.area = function() {
    return Math.PI * this.radius * this.radius;
};

var Chromo = function(pop) {
    this.fitness = 0;
    this.circle = new Circle({x: 0, y: 0, radius: 0});
    this.parent = pop;
};

Chdromo.prototype.randomize = function() {
    this.circle.x = M.random() * w;
    this.circle.y = M.random() * h;
    this.circle.radius = M.random() * 120 + 10;
};

Chromo.prototype.mutate = function() {
    var attrId = M.random() * 3 | 0;
    var value = 350 * (M.random() - 0.5);
    // 0: x, 1: y, 2: radius
    switch (attrId) {
        case 0:
            this.circle.x += 5*value;
            break;
        case 1:
            this.circle.y += 5*value;
            break;
        case 2:
            this.circle.radius += (value < -this.circle.radius) ? -value : value;
            break;
    }
};

Chromo.prototype.mutate2 = function() {
    var k = 4;
    var sign = M.random() < 0.5 ? -1 : 1;
    var r = 0.1 * w;
    var u = M.random();
    var a = 1/Math.pow(2, u*k);
    this.circle.x += M.random() < 0.33 ? sign * r * a : 0;

    sign = M.random() < 0.5 ? -1 : 1;
    r = 0.1 * h;
    u = M.random();
    a = 1/Math.pow(2, u*k);
    this.circle.y += M.random() < 0.33 ? sign * r * a : 0;

    sign = M.random() < 0.5 ? -1 : 1;
    r = 0.1 * 250;
    u = M.random();
    a = 1/Math.pow(2, u*k);
    this.circle.radius += M.random() < 0.33 ? sign * r * a : 0;

};

Chromo.prototype.crossover = function(mate) {
    var crossPoint = M.random() * 2 | 0;
    var child1 = new Chromo(this.parent), child2 = new Chromo(this.parent);
    switch (crossPoint) {
        case 0:
            child1.circle.x = this.circle.x;
            child1.circle.y = mate.circle.y;
            child1.circle.radius = mate.circle.radius;

            child2.circle.x = mate.circle.x;
            child2.circle.y = this.circle.y;
            child2.circle.radius = this.circle.radius;
            break;
        case 1:
            child1.circle.x = this.circle.x;
            child1.circle.y = this.circle.y;
            child1.circle.radius = mate.circle.radius;

            child2.circle.x = mate.circle.x;
            child2.circle.y = mate.circle.y;
            child2.circle.radius = this.circle.radius;
            break;
    }
    return [child1, child2];
};

Chromo.prototype.crossover1 = function(mate) {
    var child = new Chromo(this.parent);
    child.circle.x = M.random() < 0.5 ? this.circle.x : mate.circle.x;
    child.circle.y = M.random() < 0.5 ? this.circle.y : mate.circle.y;
    child.circle.radius = M.random() < 0.5 ? this.circle.radius : mate.circle.radius;
    return child;
};

Chromo.prototype.crossoverIntermediate = function(mate) {
    var child = new Chromo(this.parent);

    var a = M.random() * 1.5 - 0.25;
    child.circle.x = a * this.circle.x + (1-a) * mate.circle.x;

    a = M.random() * 1.5 - 0.25;
    child.circle.y = a * this.circle.y + (1-a) * mate.circle.y;

    a = M.random() * 1.5 - 0.25;
    child.circle.radius = a * this.circle.radius + (1-a) * mate.circle.radius;

    return child;
};

Chromo.prototype.calculateFitness = function() {
    for (var c = this.parent.circles.length; c--;) {
        if (this.circle.intersects(this.parent.circles[c])) {
            this.fitness = 0;
            return;
        }
    }
    var cx = this.circle.x,
        cy = this.circle.y,
        cr = this.circle.radius;
    // circle out of view
    if (cx - cr < 0 || cx + cr > w || cy - cr < 0 || cy + cr > h) {
        this.fitness = 0;
        return;
    }
    //this.fitness = 1/(1+Math.abs(this.parent.availableArea - this.circle.area()));
    this.fitness = this.circle.radius;
};

var Population = function(N) {
    this.N = (typeof N !== 'undefined') ? N : 100;
    this.generation = 0;
    this.chromos = [];
    this.circles = [];
    this.top5 = [];
    //this.availableArea = 0;
    this.showUnFit = false;
    this.totalFitness = 0;
    this.MUTATIONRATE = 0.01;
    this.CROSSOVERRATE = 0.8;
};

Population.prototype.init = function() {
    var nCircles = 10;
    var i = nCircles;
    var discard;
    var circleArea = 0;
    while (i) {
        discard = false;
        var newCircle = new Circle({radius: M.random() * 40 + 30});
        for (var len = this.circles.length; len--;) {
            if (newCircle.intersects(this.circles[len])) {
                discard = true;
                break;
            }
        }
        if (discard) continue;
        this.circles.push(newCircle);
        circleArea += newCircle.area();
        i--;
    }

    this.availableArea = w*h - circleArea;

    for (i = this.N; i--;) {
        var chromo = new Chromo(this);
        chromo.randomize();
        chromo.calculateFitness();
        this.chromos.push(chromo);
    }
    this.calculateTotalFitness();
};

Population.prototype.calculateTotalFitness = function()
{
    this.totalFitness = 0;
    for (var c = this.chromos.length; c--;) {
        this.totalFitness += this.chromos[c].fitness;
    }
};

Population.prototype.roulette = function()
{
    var sum = 0;
    var r = M.random() * this.totalFitness;
    for (var c = this.chromos.length; c--;) {
        sum += this.chromos[c].fitness;
        if (sum > r) return c;
    }
    return 0;
};

Population.prototype.runGeneration = function()
{
    this.generation++;
    var newPopulation = [];

    /*    ELITISM SELECTION
     *    this.chromos.sort(function(a, b) {
     *        return b.fitness - a.fitness;
     *    });
     *
     *    var parent1 = this.chromos[0],
     *        parent2 = this.chromos[1];
     */

    for (var len = this.N; len--;) {
        var parent1 = this.chromos[this.roulette()],
            parent2 = this.chromos[this.roulette()];
        var child = parent1;
        
        if (M.random() <= this.CROSSOVERRATE) {
            child = parent1.crossoverIntermediate(parent2);
            newPopulation.push(child);
        }
        
        if (M.random() <= this.MUTATIONRATE) {
            //this.chromos[len].mutate();
            child.mutate2();
        }

        //this.chromos[len].calculateFitness();
        child.calculateFitness();
        newPopulation.push(child);
    }
    this.chromos = newPopulation;

    if (this.generation % 100 == 1) {
        newPopulation.sort(function(a, b) {
            return b.fitness - a.fitness;
        });
        var t5 = this.top5;
        var c = newPopulation;
        t5[0] = {f: c[0].fitness};
        t5[1] = {f: c[1].fitness};
        t5[2] = {f: c[2].fitness};
        t5[3] = {f: c[3].fitness};
        t5[4] = {f: c[4].fitness};
    }

    this.calculateTotalFitness();
};

Population.prototype.draw = function() {
    ctx.fillStyle='rgba(255,255,255,0.2)';
    ctx.fillRect(0,0,w,h);

    for (len = this.chromos.length; len--;) {
        var f = this.chromos[len];

        if (!f.fitness && !this.showUnFit) continue;

        var c = f.circle;
        var sat = f.fitness/h*2;
        sat = smoothstep(smoothstep(sat));
        sat = 90*sat + 60*(1-sat);
        
        ctx.fillStyle='hsla('+[10,sat+'%','60%',0.3].join(',')+')';
        ctx.beginPath();
        ctx.arc(c.x | 0, c.y | 0, c.radius | 0, 0, 2 * Math.PI, false);
        ctx.fill();
    }

    for (var len = this.circles.length; len--;) {
        var c = this.circles[len];
        ctx.beginPath();
        ctx.arc(c.x | 0, c.y | 0, c.radius | 0, 0, 2 * Math.PI, false);
        ctx.stroke();
    }

    ctx.fillStyle = 'black';
    ctx.fillText("Generation: " + this.generation, 10, 10);
    ctx.fillText("M: " + this.MUTATIONRATE, 10, 20);
    ctx.fillText("C: " + this.CROSSOVERRATE, 10, 30);
    for (var i = 0; i < 5; i++) {
        ctx.fillText("radius: "+(this.top5[i].f*100|0)/100, 10, 40 + i * 10);
    }

};

var keyHandler = function(e) {
    if (e.keyCode == 32) {
        paused = !paused;
        run();
    }
};

var pop = new Population(30);

var crossSlider = document.getElementById('crossover');
var mutationSlider = document.getElementById('mutation');
crossSlider.value = pop.CROSSOVERRATE*100;
mutationSlider.value = pop.MUTATIONRATE*100*4;

var paused = true;
pop.init();

// Events
document.addEventListener("keydown", keyHandler, false);
crossSlider.addEventListener('change', function() {
    pop.CROSSOVERRATE = crossSlider.value/100;
}, false);
mutationSlider.addEventListener('change', function() {
    pop.MUTATIONRATE = mutationSlider.value/100/4;
}, false);

var run = function() {
    pop.runGeneration();
    pop.draw();
    if (!paused)
        setTimeout(run, 30);
};

var runDummy = function() {
    maxRadius = 0;
    var pos = {x: -1, y: -1};
    var testCircle = new Circle({x: 0, y: 0});
    for (var x = 0; x < w; x++) {
        testCircle.x = x;
        for (var y = 0; y < h; y++) {
            testCircle.y = y;
            var unfit = false;
            for (var radius = 1; radius < h/2; radius++) {
                testCircle.radius = radius;
                if (x - radius < 0 || x + radius > w || y - radius < 0 || y + radius > h) {
                    unfit = true;
                    break;
                }
                for (var c = pop.circles.length; c--;) {
                    if (testCircle.intersects(pop.circles[c])) {
                        unfit = true;
                        break;
                    }
                }
                if (unfit) break;
                if (radius > maxRadius) {
                    maxRadius = radius;
                    pos.x = x;
                    pos.y = y;
                }
            }
        }
    }
    for (var c = pop.circles.length; c--;) {
        ctx.beginPath();
        ctx.arc(pop.circles[c].x, pop.circles[c].y, pop.circles[c].radius, 0, 2*Math.PI,false);
        ctx.stroke();
    }
    ctx.fillStyle = 'rgba(10,240,10,1)';
    ctx.beginPath();
    ctx.arc(pos.x, pos.y, maxRadius, 0, 2*Math.PI,false);
    ctx.fill();
    setTimeout(run, 900);
};

//pop.draw();
//setTimeout(run, 30);
runDummy();
