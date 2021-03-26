import {setMaxIterations, renderPlot, drawBorders, drawResult, getCurrentIteration} from "./renderUtils";
import annotations from "function-plot/dist/helpers/annotations";


class OptimizationMethod {
    renderResults(results) {
        setMaxIterations(results.iterations.length - 1);
    }

    renderBorders(results) {
        const iteration = getCurrentIteration();
        const additionalData = drawResult(results);
        const additionalAnnotations = drawBorders(results, iteration);
        renderPlot(results.function, this.displayName, additionalData, additionalAnnotations);
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
        this.renderBorders(results);
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
        this.renderBorders(results);
    }
}


export {Dichotomy, GoldenRatio, Fibonacci, Parabola, Brent};
