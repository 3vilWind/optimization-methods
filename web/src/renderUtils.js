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
    // update the scales's metadata
    let plot = functionPlot(options);
    if (currentPlot !== null) {
        plot.meta.zoomBehavior = currentPlot.meta.zoomBehavior;
    }
    // plot.canvas.draw();
    currentOptions = options;
    currentPlot = plot;
    // console.log(options.xAxis.domain);
}

function drawResult(results) {
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


export {setMaxIterations, renderPlot, drawBorders, drawResult, getCurrentIteration};
