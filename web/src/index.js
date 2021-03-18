require('./styles.scss');

import functionPlot from "function-plot";

class OptimizationMethod {
    constructor(name) {
        this.name = name;
    }
}


class Function {
    constructor() {
        this.stringRepr = "-3*x*sin(0.75*x) + 2.7^(-2*x)";
    }
}


const methods = [
    new OptimizationMethod("Dichotomy"),
    new OptimizationMethod("Golden Ratio"),
    new OptimizationMethod("Fibonacci"),
    new OptimizationMethod("Parabola"),
    new OptimizationMethod("Combined Brent"),
];

function renderMethods() {
    for (const method of methods) {
        const template = `<a class="panel-block">${method.name}</a>`;
        const methodsPanel = document.body.querySelector("#methods-panel");
        methodsPanel.insertAdjacentHTML("beforeend", template);
    }
}

function attachMaxIterations() {
    const maxIterationsInput = document.body.querySelector("#maxIterationsInput");
    const currentIterationSlider = document.body.querySelector("#currentIterationSlider");
    const currentIterationSliderInput = document.body.querySelector("#currentIterationSliderInput");
    maxIterationsInput.addEventListener("change", (event) => {
        currentIterationSlider.max = maxIterationsInput.value;
        currentIterationSliderInput.max = maxIterationsInput.value;

        currentIterationSlider.value = Math.min(currentIterationSlider.value, maxIterationsInput.value);
        currentIterationSliderInput.value = Math.min(currentIterationSliderInput.value, maxIterationsInput.value);
    });
    currentIterationSlider.addEventListener("change", (event) => {
        currentIterationSliderInput.value = currentIterationSlider.value;
    });
    currentIterationSliderInput.addEventListener("change", (event) => {
        currentIterationSlider.value = currentIterationSliderInput.value;
    });
}

function renderPlot() {
    let contentsBounds = document.body.querySelector("#root-plot").getBoundingClientRect();
    let width = 16;
    let height = 9;
    let ratio = contentsBounds.width / width;
    width *= ratio;
    height *= ratio;

    functionPlot({
        target: "#root-plot",
        width,
        height,
        grid: true,
        data: [
            {
                graphType: 'polyline',
                fn: "-3*x*sin(0.75*x) + 2.7^(-2*x)",
            }
        ]
    });
}

attachMaxIterations();
renderMethods();
renderPlot();
