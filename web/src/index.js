require('./styles.scss');
import wasmBinary from "./core.wasm";

import Module from "./core.js";

import {base64ToBytes} from "./utils";
import {Brent, Dichotomy, Fibonacci, GoldenRatio, Parabola} from "./methods";
import {renderPlot, setMaxIterations} from "./renderUtils";
import {parse} from "mathjs";

const modulePath = {
    wasmBinary: base64ToBytes(wasmBinary)
};
Module(modulePath).then(wasmInit);
let module = null;


let currentResults = null;
let currentMethod = null;
let currentFunction = functionVar8;


const methods = [
    new Dichotomy(),
    new GoldenRatio(),
    new Fibonacci(),
    new Parabola(),
    new Brent(),
];

function evalFunction(compiled) {
    return function (x) {
        return compiled.evaluate({x: x});
    }
}

function renderMethods() {
    for (const method of methods) {
        const template = `<a class="panel-block">${method.displayName}</a>`;
        const methodsPanel = document.body.querySelector("#methods-panel");
        methodsPanel.insertAdjacentHTML("beforeend", template);
        methodsPanel.lastChild.addEventListener("click", (e) => {
            const functionInput = document.querySelector("#functionInput");
            const leftBorderInput = document.querySelector("#leftBorderInput");
            const rightBorderInput = document.querySelector("#rightBorderInput");
            const epsilonInput = document.querySelector("#epsilonInput");
            currentFunction = evalFunction(parse(functionInput.value).compile());
            const results = callOptimizationMethod(currentFunction, method.coreName, parseFloat(leftBorderInput.value), parseFloat(rightBorderInput.value), parseFloat(epsilonInput.value));
            results.function = currentFunction;
            currentResults = results;
            currentMethod = method;
            renderIteration();
        });
    }
}


function initIterationsSync() {
    const currentIterationSlider = document.body.querySelector("#currentIterationSlider");
    const currentIterationSliderInput = document.body.querySelector("#currentIterationSliderInput");
    currentIterationSlider.addEventListener("change", (event) => {
        currentIterationSliderInput.value = currentIterationSlider.value;
        renderIteration(currentIterationSliderInput.value);
    });
    currentIterationSliderInput.addEventListener("change", (event) => {
        currentIterationSlider.value = currentIterationSliderInput.value;
        renderIteration(currentIterationSlider.value);
    });
}


function functionVar8(x) {
    return -3 * x * Math.sin(0.75 * x) + Math.exp(-2 * x);
}

function wasmInit(mod) {
    module = mod;
    const pageloader = document.querySelector("#pageloader");
    pageloader.classList.remove("is-active");

    setMaxIterations(0);
    initIterationsSync();
    renderMethods();
    // renderPlot(currentFunction, []);
}

function callOptimizationMethod(f, method, left, right, epsilon) {
    const functionVar8Ptr = module.addFunction(f, "dd");
    let callResult = module.callOptimizationMethod(JSON.stringify({
        method: method,
        left: left,
        right: right,
        epsilon: epsilon,
        function: functionVar8Ptr
    }));
    module.removeFunction(functionVar8Ptr);
    return JSON.parse(callResult);
}

function renderIteration(iteration) {
    if (currentResults === null || currentMethod === null)
        return;
    currentMethod.renderResults(currentResults, iteration);
}