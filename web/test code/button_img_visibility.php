<img id="myImg1" src="/img/signal.png">
<img id="myImg2" src="/img/sheffield.jpeg">
<img id="myImg3" src="/img/fft.png">
<br>

<button type="button" onclick="Voltage()">Voltage and current</button>
<button type="button" onclick="Power()">Power</button>
<button type="button" onclick="Interferance()">Interferance</button>

<script>
function Voltage() {
    document.getElementById("myImg1").style.visibility = "visible";
    document.getElementById("myImg2").style.visibility = "hidden";
    document.getElementById("myImg3").style.visibility = "hidden";  
}

function Power() {
    document.getElementById("myImg1").style.visibility = "hidden";
    document.getElementById("myImg2").style.visibility = "visible";
    document.getElementById("myImg3").style.visibility = "hidden";
}

function Interferance() {
    document.getElementById("myImg1").style.visibility = "hidden";
    document.getElementById("myImg2").style.visibility = "hidden";
    document.getElementById("myImg3").style.visibility = "visible"; 
}

</script>

--------------------------------------------------------------------

	function button1() {
    document.getElementById("myImg1").style.visibility = "visible";
    document.getElementById("myImg2").style.visibility = "hidden";
    document.getElementById("myImg3").style.visibility = "hidden";
    document.getElementById("myImg4").style.visibility = "hidden";
	}
		

	function button2() {
    document.getElementById("myImg1").style.visibility = "hidden";
    document.getElementById("myImg2").style.visibility = "visible";
    document.getElementById("myImg3").style.visibility = "hidden";
    document.getElementById("myImg4").style.visibility = "hidden";
	}

		
	function button3() {
    document.getElementById("myImg1").style.visibility = "hidden";
    document.getElementById("myImg2").style.visibility = "hidden";
    document.getElementById("myImg3").style.visibility = "visible";
    document.getElementById("myImg4").style.visibility = "visible";
	}

--------------------------------------------------------------------
    
    <div id="idimg" class="class1">
        <img data-src="/img/signal.png">
        <img data-src="/img/under.png">
        <img data-src="/img/fft_0_20kHz.png">
        <img data-src="/img/fft_0_90kHz.png">
    </div>


    function button1() {
    document.getElementById('idimg').style.maxHeight = "200px";
    var images = document.querySelectorAll("#idimg img");
    images[0].src = images[0].getAttribute('data-src');
    images[0].style.visibility = "visible";
    images[1].style.visibility = "hidden";
    images[2].style.visibility = "hidden";
    }
        

    function button2() {
    document.getElementById('idimg').style.maxHeight = "200px";
    var images = document.querySelectorAll("#idimg img");
    images[1].src = images[1].getAttribute('data-src');
    images[0].style.visibility = "hidden";
    images[1].style.visibility = "visible";
    images[2].style.visibility = "hidden";
    }

        
    function button3() {
    document.getElementById('idimg').style.maxHeight = "200px";
    var images = document.querySelectorAll("#idimg img");
    images[2].src = images[2].getAttribute('data-src');
    images[0].style.visibility = "hidden";
    images[1].style.visibility = "hidden";
    images[2].style.visibility = "visible";
    }
