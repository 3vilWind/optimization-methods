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
            plot.evalCommand(this.getLevelCommand(results.f, this.evaluateFunction(results.f, iteration.x, iteration.y), levelName));
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
        return `${name}: 0.5 * (${f.xx} * x^2 + ${f.xy} * x * y + ${f.yy} * y^2) + ${f.x} * x + ${f.y} * y + ${f.c} = ${z}`;
    }

    getPointCommand(x, y, name) {
        return `${name} = (${x}, ${y})`
    }

    getVectorCommand(fromX, fromY, toX, toY, name) {
        return `${name} = Vector((${fromX}, ${fromY}), (${toX}, ${toY}))`
    }

    evaluateFunction(f, x, y) {
        return 0.5 * (f.xx * x * x + f.xy * x * y + f.yy * y * y) + f.x * x + f.y * y + f.c;
    }
}


class GradientDescent extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Gradient Descent";
        this.coreName = "GRADIENT_DESCENT";
    }
}

class GradientSteepestDescent extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Gradient Steepest Descent";
        this.coreName = "GRADIENT_STEEPEST_DESCENT";
    }
}


class ConjugateGradientMethod extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Conjugate Gradient Method";
        this.coreName = "CONJUGATE_GRADIENT_METHOD";
    }
}


export {GradientDescent, GradientSteepestDescent, ConjugateGradientMethod};
