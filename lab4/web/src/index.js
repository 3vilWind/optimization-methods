import {options} from "./options";
import wasmBinary from "./core.wasm";

import Module from "./core.js";

import {base64ToBytes} from "./utils";
import {DescentNewton, ClassicNewton, LinearSearchNewton, Bfghs, Powell, Marquardt, MarquardtCholesky} from "./methods";
import {resetPlot, setMaxIterations} from "./renderUtils";

require('./styles.scss');

const modulePath = {
    wasmBinary: base64ToBytes(wasmBinary)
};
Module(modulePath).then(wasmInit);
let module = null;

let currentResults = null;
let currentMethod = null;
let currentFunction = null;
let currentIteration = -1;


const methods = [
    new ClassicNewton(),
    new LinearSearchNewton(),
    new DescentNewton(),
    new Bfghs(),
    new Powell(),
    new Marquardt(),
    new MarquardtCholesky(),
];


function renderMethods() {
    for (const method of methods) {
        const template = `<a id="block-${method.coreName}" class="panel-block">${method.displayName}</a>`;
        const methodsPanel = document.body.querySelector("#methods-panel");
        const functionSelect = document.querySelector("#function-select");
        methodsPanel.insertAdjacentHTML("beforeend", template);
        methodsPanel.lastChild.addEventListener("click", (e) => {
            for (const i of methods) {
                const obj = document.querySelector(`#block-${i.coreName}`);
                if (i.coreName !== method.coreName) {
                    obj.classList.remove("has-background-light");
                } else {
                    obj.classList.add("has-background-light");
                }
            }

            const startX = parseFloat(document.querySelector("#start-x").value);
            const startY = parseFloat(document.querySelector("#start-y").value);

            const epsilon = parseFloat(document.querySelector("#epsilon").value);

            currentFunction = functionSelect.value;
            currentResults = callOptimizationMethod(currentFunction, method.coreName, startX, startY, epsilon);
            currentResults.f = currentFunction;
            currentMethod = method;
            renderIteration(-1, 0);
            currentIteration = 0;
        });
    }
}


function initIterationsSync() {
    const currentIterationSlider = document.body.querySelector("#currentIterationSlider");
    const currentIterationSliderInput = document.body.querySelector("#currentIterationSliderInput");
    currentIterationSlider.addEventListener("change", (event) => {
        const newValue = parseInt(currentIterationSlider.value);
        currentIterationSliderInput.value = currentIterationSlider.value;
        renderIteration(currentIteration, newValue);
        currentIteration = newValue;
    });
    currentIterationSliderInput.addEventListener("change", (event) => {
        const newValue = parseInt(currentIterationSliderInput.value);
        currentIterationSlider.value = currentIterationSliderInput.value;
        renderIteration(currentIteration, newValue);
        currentIteration = newValue;
    });
}

function initOptionsSync() {
    const checkboxes = [
        {
            selector: "#show-levels-checkbox",
            name: "showLevels"
        },
        {
            selector: "#show-arrows-checkbox",
            name: "showArrows"
        },
        {
            selector: "#show-axis-checkbox",
            name: "showAxis"
        },
        {
            selector: "#show-grid-checkbox",
            name: "showGrid"
        }];

    for (let i of checkboxes) {
        const obj = document.querySelector(i.selector);
        obj.addEventListener("change", (event) => {
            const result = event.target.checked;
            options[i.name] = result;
            if (i.name === "showLevels") {
                updateLevelsVisibility();
            } else if (i.name === "showArrows") {
                updateArrowsVisibility();
            } else if (i.name === "showAxis") {
                window.plot.setAxesVisible(result, result);
            } else if (i.name === "showGrid") {
                window.plot.setGridVisible(result);
            }
        });
    }
}


function wasmInit(mod) {
    module = mod;

    setMaxIterations(0);
    initIterationsSync();
    initOptionsSync();
    renderMethods();

    let contentsBounds = document.body.querySelector("#plot").getBoundingClientRect();
    let width = 16;
    let height = 9;
    let ratio = contentsBounds.width / width;
    width *= ratio;
    height *= ratio;
    const params = {
        "id": "plot",
        "appName": "classic",
        "width": width,
        "height": height,
        "showToolBar": false,
        "showToolBarHelp": false,
        "showAlgebraInput": false,
        "showMenuBar": false,
        "enableUndoRedo": false,
        "showResetIcon": false,
        "enableShiftDragZoom": true,
        "ggbBase64": "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",
        "allowStyleBar": false,
        "enableLabelDrags": false,
        "enableRightClick": false,
        "appletOnLoad": function () {
            resetPlot();
            const pageloader = document.querySelector("#pageloader");
            pageloader.classList.remove("is-active");
        }
    };
    const ggbApplet = new GGBApplet(params, true);
    ggbApplet.inject('plot');
}

function callOptimizationMethod(f, method, startX, startY, epsilon) {
    const request = JSON.stringify({
        method: method,
        startPoint: {
            x: startX,
            y: startY
        },
        epsilon: epsilon,
        function: f
    });
    let callResult = module.callOptimizationMethod(request);
    console.log(request);
    console.log(callResult);
    return JSON.parse(callResult);
}

function renderIteration(prev, next) {
    if (currentResults === null || currentMethod === null)
        return;
    currentMethod.renderResults(currentResults, prev, next);
}


function updateLevelsVisibility() {
    currentMethod.updateLevelsVisibility(currentIteration);
}

function updateArrowsVisibility() {
    currentMethod.updateArrowsVisibility(currentIteration);
}
