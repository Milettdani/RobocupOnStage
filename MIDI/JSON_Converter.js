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

function CopyDrums() {
var copyText = document.getElementById("resultTextarea");
var text = document.getElementById("resultTextarea").value;
copyText.select();
copyText.setSelectionRange(text.indexOf("Drums:")+7, text.indexOf("Piano")-1);
document.execCommand("copy");
}		//	PASTE INTO DrumsRead.txt

function CopyPiano() {
var copyText = document.getElementById("resultTextarea");
var text = document.getElementById("resultTextarea").value;
copyText.select();
copyText.setSelectionRange(text.indexOf("Piano:")+7, 9999999);
document.execCommand("copy");
}		//	PASTE INTO PianoRead.txt

var final = "";
const input = document.querySelector('input[type="file"]');
input.addEventListener('change', function (e) {
//console.log(input.files)
const reader = new FileReader()
reader.onload = function() {
	var parsedMusic = JSON.parse(reader.result)
	console.log(parsedMusic)

	var d = true;
	var p = true;
	for (var i = 0; i < Object.size(parsedMusic.tracks); i++) {
		//Creat arrays
		if (Object.size(parsedMusic.tracks[i].notes) > 0) {
			var t = "";
			var fw = "";
			var pw = "";
			if ((JSON.stringify(parsedMusic.tracks[i]).includes('isPercussion') && parsedMusic.tracks[i].isPercussion) || Object.size(parsedMusic.tracks || !p) == 1) {
				if (d == true) {
					t = "const double d" + "[" + Object.size(parsedMusic.tracks[i].notes) * 2 + "] = {"
					fw = Object.size(parsedMusic.tracks[i].notes) * 2 + "\n";
					for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
						if (j > 0) {
							t += ", ";
							fw += "\n";
						}
						t += parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time.toFixed(2);
						fw += parsedMusic.tracks[i].notes[j].midi + "\n" + parsedMusic.tracks[i].notes[j].time.toFixed(2);
					}
					d = false;
					console.log(fw);
					//WriteToFile(t + "};");
				}
			} else {
				if (p == true) {
					t = "const double p" + "[" + Object.size(parsedMusic.tracks[i].notes) * 3 + "] = {"
					pw = parsedMusic.tracks[i].notes[0].midi + "\n" + Object.size(parsedMusic.tracks[i].notes) * 3 + "\n";
					for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
						if (j > 0) {
							t += ", "
							pw += "\n"
						}
						t += parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time.toFixed(2) + ", " + parsedMusic.tracks[i].notes[j].duration.toFixed(2);
						pw += parsedMusic.tracks[i].notes[j].midi + "\n" + parsedMusic.tracks[i].notes[j].time.toFixed(2) + "\n" + parsedMusic.tracks[i].notes[j].duration.toFixed(2);
					}
					p = false
				}
			}
			final += t + "};\n"
			if (i == Object.size(parsedMusic.tracks)-1) final += '\n\nDrums:\n' + fw + "\nPiano:\n" + pw;
	}
	}
	document.getElementById("resultTextarea").value = final;
}
reader.readAsText(input.files[0])
}, false);
