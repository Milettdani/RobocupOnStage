//if isPercussion == true:
//	midi: 42 -> closed hi-hat
//	midi: 46 -> open hi-hat
//	midi: 55 -> crash
//	midi: 36 -> kick
//	midi: 38 -> snare
//else:
//	midi: 60 -> C4

Object.size = function(obj) {
		var size = 0, key;
		for (key in obj) {
				if (obj.hasOwnProperty(key)) size++;
		}
		return size;
};

function Copy() {
	var copyText = document.getElementById("resultTextarea");
	copyText.select();
	copyText.setSelectionRange(0, 99999);
	document.execCommand("copy");
}

var final = "";
const input = document.querySelector('input[type="file"]');
input.addEventListener('change', function (e) {
	//console.log(input.files)
	const reader = new FileReader()
	reader.onload = function() {
		var parsedMusic = JSON.parse(reader.result)
		console.log(parsedMusic)

		var t = [];
		var d = true;
		var p = true;
		for (var i = 0; i < Object.size(parsedMusic.tracks); i++) {
			//Creat arrays
			if (Object.size(parsedMusic.tracks[i].notes) > 0) {
				if (JSON.stringify(parsedMusic.tracks[i]).includes('isPercussion') && parsedMusic.tracks[i].isPercussion) {
					if (d == true) {
						t[i] = "double d" + "[" + Object.size(parsedMusic.tracks[i].notes) * 2 + "] = {"
						//console.log("int t" + i + "[" + Object.size(parsedMusic.tracks[i].notes) + "] = ")
						//Creat elements
						var toNext = 0

						for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
							if (j > 0) {
                                                                toNext = parsedMusic.tracks[i].notes[j].time - parsedMusic.tracks[i].notes[j-1].time
                                                        } else {
								toNext = parsedMusic.tracks[i].notes[j].time
							}


							if (j > 0) {
								t[i] += ", "
							}
							t[i] += parsedMusic.tracks[i].notes[j].midi + ", " + toNext.toFixed(2);
							//console.log(parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time + ", " + parsedMusic.tracks[i].notes[j].duration)
						}
						d = false
					}
				} else {
					if (p == true) {
						t[i] = "double p" + "[" + Object.size(parsedMusic.tracks[i].notes) * 3 + "] = {"
						for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
							if (j > 0) t[i] += ", "
							t[i] += parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time.toFixed(2) + ", " + parsedMusic.tracks[i].notes[j].duration.toFixed(2);
						}
						p = false
					}
				}
					t[i] += "};"
					final += t[i] + "\n"
					//console.log(final)
		}
		}
		//document.getElementById("resultTextarea").value = final;
	}
	reader.readAsText(input.files[0])
}, false);

function onSubmit() {
	document.getElementById("resultTextarea").value = final;
}
