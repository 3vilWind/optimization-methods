function setMaxIterations(value, dropIterations=false) {
    const currentIterationSlider = document.body.querySelector("#currentIterationSlider");
    const currentIterationSliderInput = document.body.querySelector("#currentIterationSliderInput");

    currentIterationSlider.max = value;
    currentIterationSliderInput.max = value;

    if (dropIterations) {
        currentIterationSlider.value = 0;
        currentIterationSliderInput.value = 0;
    } else {
        currentIterationSlider.value = Math.min(currentIterationSlider.value, value);
        currentIterationSliderInput.value = Math.min(currentIterationSliderInput.value, value);
    }
}


function resetPlot() {
    const plot = window.plot;
    plot.newConstruction();
    plot.setAxisLabels(1, "x", "y", "z");
}


export {setMaxIterations, resetPlot};
