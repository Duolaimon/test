  function thousandPartition(num){
		var source=String(num).split(".");
		var b=/(\d)(?=(\d{3})+$)/g;
		source[0]=source[0].replace(b,"$1,");
		return source.join(".");
	}
