
	function blink_text() {
    	$("#blink").fadeOut(500);
    	$("#blink").fadeIn(500);
	}
	setInterval(blink_text, 1000);
	$(document).ready(function(){
		var data = {
		    'IIITH': 'IIITH',
		    'IITB': 'IITB',
		    'IITD':'IITD',
		    'IITM':'IITM',
		    'IITG':'IITG',
		    'IITK':'IITK'
		}
		var str = $('<select />');
		for(var val in data) {
		    $('<option />', {value: val, text: data[val]}).appendTo(str);
		}
		str.appendTo('h3');

		$("#btn").click(function(){
	  		$('#image').css("background-image", "url(/home/rishabh/F/MTECH/Software-Systems-Development/lab4/img.jpg)");
	  	});
	  	$("#keyPress").on("keypress", function(event){
	  		var key = (event.keyCode ? event.keyCode : event.which); 
	  		var inp=$("#keyPress").val();
	  		if (key == 51) {
  				alert(" key 3 is pressed ");	
			}
		});

});

	