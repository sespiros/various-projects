var c = document.getElementById('screen');
var w = c.width = window.innerWidth, h = c.height;
var ctx = c.getContext('2d');

// bootstrap prng
var M = new MersenneTwister();

var best = [100,100,100];

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
}

var Chromo = function(pop) {
    this.fitness = 0;
    this.circle = new Circle({x: 0, y: 0, radius: 0});
    this.parent = pop;
};

Chromo.prototype.randomize = function() {
    this.circle.x = M.random() * w;
    this.circle.y = M.random() * h;
    this.circle.radius = M.random() * 120 + 10;
};

Chromo.prototype.mutate = function()
{ 
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

}

Chromo.prototype.crossover = function(mate)
{
    var child0 = new Chromo(this.parent);
    var child1 = new Chromo(this.parent);
    child0.circle.x = this.circle.x;
    child0.circle.y = this.circle.y;
    child0.circle.radius = mate.circle.radius;

    child1.circle.x = mate.circle.x;
    child1.circle.y = mate.circle.y;
    child1.circle.radius = this.circle.radius;
    return [child0,child1];
};

Chromo.prototype.calculateFitness = function()
{
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
    this.fitness = this.circle.radius;
};

var Population = function(N)
{
    this.N = (typeof N !== 'undefined') ? N : 100;
    this.generation = 0;
    this.chromos = [];
    this.circles = [];
    this.MUTATIONRATE = 0.25;
    this.CROSSOVERRATE = 0.6;
};

Population.prototype.init = function()
{
    var nCircles = 20;
    var i = nCircles;
    var discard;
    var circleArea = 0;
    while (i) {
        discard = false;
        var newCircle = new Circle({radius: M.random() * 40 + 20});
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
};

Population.prototype.runGeneration = function()
{
    this.generation++;
    var newPopulation = [];

    /* ELITISM SELECTION */
    this.chromos.sort(function(a, b) {
		    return b.fitness - a.fitness;
		    });

    newPopulation.push(this.chromos[0]);
    newPopulation.push(this.chromos[1]);

    for (var len = this.N; len>2; len--) {
	var parent1 = this.chromos[M.random()*(this.N-1)|0];
	var parent2 = this.chromos[M.random()*(this.N-1)|0];
	var children = [parent1,parent2];
	while(parent2==parent1){
		parent2 = this.chromos[M.random()*(this.N-1)|0];
	}
        
        if (M.random() <= this.CROSSOVERRATE) {
            children = parent1.crossover(parent2);
        }
        
        if (M.random() <= this.MUTATIONRATE) {
            children[0].mutate();
        }

        if (M.random() <= this.MUTATIONRATE) {
            children[1].mutate();
        }

        children[0].calculateFitness();
        children[1].calculateFitness();
        newPopulation.push(children[0]);
        newPopulation.push(children[1]);
    }
    this.chromos = newPopulation;

};

Population.prototype.draw = function() 
{
    ctx.fillStyle = 'hsl(111, 100%, 27%)';
    ctx.beginPath();
    ctx.arc(best[0],best[1],best[2], 0, 2 * Math.PI, false);
    ctx.fill();

    ctx.fillStyle='rgba(255,255,255,0.2)';
    ctx.fillRect(0,0,w,h);

    for (len = this.chromos.length; len--;) {
        var f = this.chromos[len];

        if (!f.fitness) continue;

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
};

var rundummy = function(){
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
	
	return [pos.x, pos.y, maxRadius];

};

var keyHandler = function(e) {
    if (e.keyCode == 32) {
        paused = !paused;
        run();
    }
};

var pop = new Population(100);

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
})

var run = function() {
    pop.runGeneration();
    pop.draw();
    if (!paused)
        setTimeout(run, 30);
};

best = rundummy();
pop.draw();
setTimeout(run, 30);
