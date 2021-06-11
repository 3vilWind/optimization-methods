import {resetPlot, setMaxIterations} from "./renderUtils";
import {options} from "./options";


class OptimizationMethod {
    renderResults(results, prevIteration, nextIteration) {
        const plot = window.plot;
        if (prevIteration === -1) {
            setMaxIterations(results.iterations.length - 1, true);
            resetPlot();
        } else if (nextIteration < prevIteration) {
            for (let i = prevIteration; i > nextIteration; i--) {
                plot.deleteObject(`L${i}`);
                plot.deleteObject(`P${i}`);
                plot.deleteObject(`V${i}`);
            }
        }

        for (let i = prevIteration + 1; i <= nextIteration; i++) {
            const levelName = `L${i}`;
            const pointName = `P${i}`;
            const vectorName = `V${i}`;
            const iteration = results.iterations[i];
            const levelCmd = this.getLevelCommand(results.f, this.evaluateFunction(results.additional, i), levelName);
            console.log(levelCmd);
            plot.evalCommand(levelCmd);
            plot.evalCommand(this.getPointCommand(iteration.x, iteration.y, pointName));
            if (i - 1 >= 0) {
                const prev = results.iterations[i - 1];
                plot.evalCommand(this.getVectorCommand(prev.x, prev.y, iteration.x, iteration.y, vectorName));
                plot.setFixed(vectorName, true, false);
                plot.setVisible(vectorName, options.showArrows);
            }

            plot.setFixed(pointName, true, false);
            plot.setFixed(levelName, true, false);

            plot.setVisible(levelName, options.showLevels);
        }
    }

    updateLevelsVisibility(iteration) {
        for (let i = 0; i <= iteration; i++) {
            const levelName = `L${i}`;
            plot.setVisible(levelName, options.showLevels);
        }
    }

    updateArrowsVisibility(iteration) {
        for (let i = 0; i <= iteration; i++) {
            const vectorName = `V${i}`;
            plot.setVisible(vectorName, options.showArrows);
        }
    }

    getLevelCommand(f, z, name) {
        if (f === "F_1_1_1") {
            return `${name}: x^2 +4y^2 +2xy = ${z.toFixed(10)}`;
        } else if (f === "F_1_1_2") {
            return `${name}: 0.25*x^4+y^4+x^2 = ${z.toFixed(10)}`;
        } else if (f === "F_1_2_1") {
            return `${name}: x^2 + y^2 -1.2*x*y = ${z.toFixed(10)}`;
        } else if (f === "F_1_2_2") {
            return `${name}: 100*(y-x^2)^2+(1-x)^2 = ${z.toFixed(10)}`;
        }else if (f === "F_2_1") {
            return `${name}: 100*(y-x^2)^2+(1-x)^2 = ${z.toFixed(10)}`;
        }else if (f === "F_2_2") {
            return `${name}: (x^2 + y - 11)^2 + (x + y^2 -7)^2 = ${z.toFixed(10)}`;
        }else if (f === "F_2_4") {
            return `${name}: 100 - 2/(1+((x-1)/2)^2+((y-1)/3)^2) - 1/(1+((x-2)/2)^2+((y-1)/3)^2) = ${z.toFixed(10)}`;
        }
        return "";
    }

    getPointCommand(x, y, name) {
        return `${name} = (${x.toFixed(10)}, ${y.toFixed(10)})`
    }

    getVectorCommand(fromX, fromY, toX, toY, name) {
        return `${name} = Vector((${fromX.toFixed(10)}, ${fromY.toFixed(10)}), (${toX.toFixed(10)}, ${toY.toFixed(10)}))`
    }

    evaluateFunction(additional, iteration) {
        return additional[iteration]["result"];
    }
}


class ClassicNewton extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Classic Newton";
        this.coreName = "CLASSIC_NEWTON";
    }
}

class LinearSearchNewton extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Linear Search Newton";
        this.coreName = "LINEAR_SEARCH_NEWTON";
    }
}


class DescentNewton extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Descent Newton";
        this.coreName = "DESCENT_NEWTON";
    }
}


class Bfghs extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "B-F-G-SH";
        this.coreName = "BFGSH";
    }
}


class Powell extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Powell";
        this.coreName = "POWELL";
    }
}


class Marquardt extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Marquardt";
        this.coreName = "MARQUARDT";
    }
}


class MarquardtCholesky extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Marquardt Cholesky";
        this.coreName = "MARQUARDT_CHOLESKY";
    }
}


export {ClassicNewton, LinearSearchNewton, DescentNewton, Bfghs, Powell, Marquardt, MarquardtCholesky};
