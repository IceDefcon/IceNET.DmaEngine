
var truepower = 2270
var appapower = 3210
var reacpower = 2270


window.onload = function () {
	var chart = new CanvasJS.Chart("chartContainer",
	{
		title:{
			text: "Decomposition of the Power in the System"
		},
		legend: {
			maxWidth: 1000,
			itemWidth: 210
		},
		data: [
		{
			type: "pie",
			showInLegend: true,
			legendText: "{indexLabel}",
			dataPoints: [
				{ y: truepower, indexLabel: "True Power" },
				{ y: appapower, indexLabel: "Apparent Power" },
				{ y: reacpower, indexLabel: "Reactive power" },
			]
		}
		]
	});
	chart.render();
}