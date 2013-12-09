var func = { 
    init : function() {

		function initialize() {

			// map options
			var mapOptions = {
				center: new google.maps.LatLng(37.871432,-122.258499),
				zoom: 16
			};

			// marker
			var latlong = new google.maps.LatLng(37.871432,-122.258499);
			var markers = [
				['South Hall', 37.871432, -122.258499, '_images/00.jpg'],
				['California Memorial Stadium', 37.87101 ,-122.250754, '_images/01.jpg'],
				['Soda Hall', 37.875006, -122.255752, '_images/02.jpg'],
				['Dwinelle Hall', 37.870788, -122.260516, '_images/03.jpg'],
				['Wurster Hall', 37.870737, -122.254572, '_images/04.jpg'],
				['Haas School of Business', 37.871233, -122.252793, '_images/05.jpg']
			];
			var contentString = "<div class='map-modal'><img src='_images/test.jpg' /></div>";
			var infowindow = new google.maps.InfoWindow();

			// draw map
			var map = new google.maps.Map(document.getElementById("map-canvas"), mapOptions);
			for(i=0; i<markers.length; i++) {
				marker = new google.maps.Marker({
					position: new google.maps.LatLng(markers[i][1], markers[i][2]),
					map: map
				});
				google.maps.event.addListener(marker, 'click', (function(marker, i) {
					return function() {
						infowindow.setContent("<div class='map-modal'><img src='"+ markers[i][3] + "' /></div>");
						infowindow.open(map, marker);
					}
				}) (marker, i));

			};

		}

		// load map
		google.maps.event.addDomListener(window, 'load', initialize);

    }

};

$(document).ready(function() {
	func.init();
});
