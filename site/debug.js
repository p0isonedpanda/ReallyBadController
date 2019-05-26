setInterval(() => {
    $.ajax({url: "debug.php"}).done((output) => {
    	$("#debug").html(output);
    });
}, 50);
