
$('#add').click(function() {
	console.log('add')
	id = $("#id").html()
	console.log(id)
	arr = []
	$(".list").each(function() {
		arr.push($(this).val())
	})
	arr.push($("#text").val())
	console.log(arr)
	$.ajax({
		url: 'script.php',
		type: 'PUT',
		data: { 'userInfo' : arr }
		success: function(response) {
			console.log(response)
		}
	});
})
