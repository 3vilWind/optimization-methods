import functionPlot from "function-plot";

function setMaxIterations(value) {
    const currentIterationSlider = document.body.querySelector("#currentIterationSlider");
    const currentIterationSliderInput = document.body.querySelector("#currentIterationSliderInput");

    currentIterationSlider.max = value;
    currentIterationSliderInput.max = value;

    currentIterationSlider.value = Math.min(currentIterationSlider.value, value);
    currentIterationSliderInput.value = Math.min(currentIterationSliderInput.value, value);
}

let currentPlot = null;
let currentOptions = null;

function renderPlot(f, title, additionalData = [], additionalAnnotations = []) {
    let contentsBounds = document.body.querySelector("#root-plot").getBoundingClientRect();
    let width = 16;
    let height = 9;
    let ratio = contentsBounds.width / width;
    width *= ratio;
    height *= ratio;

    const data = [
        {
            graphType: 'polyline',
            fn: (scope) => f(scope.x),
        }
    ];
    const options = {
        target: "#root-plot",
        title: title,
        grid: true,
        width: width,
        height: height,
        data: [...data, ...additionalData],
        annotations: additionalAnnotations,
    };

    if (currentOptions !== null) {
        options.xAxis = currentOptions.xAxis;
        options.yAxis = currentOptions.yAxis;
    }

    let plot = functionPlot(options);
    if (currentPlot !== null) {
        plot.meta.zoomBehavior = currentPlot.meta.zoomBehavior;
    }

    currentOptions = options;
    currentPlot = plot;

}

function drawPoint(results) {
    return [{
        points: [
            [results.result, results.function(results.result)],
        ],
        fnType: 'points',
        graphType: 'scatter'
    }];
}


function getCurrentIteration() {
    return document.body.querySelector("#currentIterationSliderInput").value;
}

function drawBorders(results, iteration) {
    return [
        {x: results.iterations[iteration].left, text: "left"},
        {x: results.iterations[iteration].right, text: "right"}
    ];
}

function renderParabola(iteration) {
    if (iteration.parabolaA !== undefined && iteration.parabolaB !== undefined && iteration.parabolaC !== undefined) {
        return [{
            fn: `${iteration.parabolaA} * x^2 + ${iteration.parabolaB} * x + ${iteration.parabolaC}`,
            graphType: "polyline"
        }];
    }
    return [];
}


function fixParabola() {
    const glitchLine = document.querySelector("#root-plot .canvas .graph .line-2");
    if (glitchLine !== null)
        glitchLine.parentElement.remove();
}

export {setMaxIterations, renderPlot, drawBorders, drawPoint, getCurrentIteration, renderParabola, fixParabola};
