var truepower = 5988.00415209
var appapower = 9580.80664334
var reacpower = 7479.01478884
window.onload = function () {CanvasJS.addColorSet("greenShades",["#0000CF","#00CF00","#CF0000"]);
var chart = new CanvasJS.Chart("chartContainer",{colorSet: "greenShades",
title:{text: "Phase L1"},legend: {maxWidth: 1000,itemWidth: 210},data: [{
type: "pie",showInLegend: true,legendText: "{indexLabel}",dataPoints: [
{ y: truepower, indexLabel: "True Power" },{ y: appapower, indexLabel: "Apparent Power" },
{ y: reacpower, indexLabel: "Reactive power" },]}]});chart.render();}