import {
    drawBorders,
    drawPoint, fixParabola,
    getCurrentIteration,
    renderParabola,
    renderPlot,
    setMaxIterations
} from "./renderUtils";


class OptimizationMethod {
    renderResults(results) {
        setMaxIterations(results.iterations.length - 1);
    }

    renderBorders(results, moreData = []) {
        if (moreData.length === 0)
            fixParabola();
        const iteration = getCurrentIteration();
        const additionalData = drawPoint(results);
        const additionalAnnotations = drawBorders(results, iteration);
        renderPlot(results.function, this.displayName, [...additionalData, ...moreData], additionalAnnotations);
    }
}


class Dichotomy extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Dichotomy";
        this.coreName = "DICHOTOMY";
    }

    renderResults(results) {
        super.renderResults(results);
        this.renderBorders(results);
    }
}

class GoldenRatio extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Golden Ratio";
        this.coreName = "GOLDEN_RATIO";
    }

    renderResults(results) {
        super.renderResults(results);
        this.renderBorders(results);
    }
}


class Fibonacci extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Fibonacci";
        this.coreName = "FIBONACCI";
    }

    renderResults(results) {
        super.renderResults(results);
        this.renderBorders(results);
    }
}

class Parabola extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Parabola";
        this.coreName = "PARABOLA";
    }

    renderResults(results) {
        super.renderResults(results);
        const iteration = getCurrentIteration();
        this.renderBorders(results, renderParabola(results.iterations[iteration]));
    }
}

class Brent extends OptimizationMethod {
    constructor() {
        super();
        this.displayName = "Combined Brent";
        this.coreName = "BRENT";
    }

    renderResults(results) {
        super.renderResults(results);
        const iteration = getCurrentIteration();
        this.renderBorders(results, renderParabola(results.iterations[iteration]));
    }
}


export {Dichotomy, GoldenRatio, Fibonacci, Parabola, Brent};
