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

function WriteToFile(arr)
{
var fso = new ActiveXObject("Scripting.FileSystemObject");
var s = fso.CreateTextFile("C:\\drumsRead.txt", true);
s.WriteLine(arr);
s.Close();
}

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
			if (JSON.stringify(parsedMusic.tracks[i]).includes('isPercussion') && parsedMusic.tracks[i].isPercussion) {
				if (d == true) {
					t = "const double d" + "[" + Object.size(parsedMusic.tracks[i].notes) * 2 + "] = {"
					for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
						if (j > 0) t += ", "
						t += parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time.toFixed(2);
					}
					d = false;
					//WriteToFile(t + "};");
				}
			} else {
				if (p == true) {
					t = "const double p" + "[" + Object.size(parsedMusic.tracks[i].notes) * 3 + "] = {"
					for (var j = 0; j < Object.size(parsedMusic.tracks[i].notes); j++) {
						if (j > 0) t += ", "
						t += parsedMusic.tracks[i].notes[j].midi + ", " + parsedMusic.tracks[i].notes[j].time.toFixed(2) + ", " + parsedMusic.tracks[i].notes[j].duration.toFixed(2);
					}
					p = false
				}
			}
			final += t + "};\n"
	}
	}
	//document.getElementById("resultTextarea").value = final;
}
reader.readAsText(input.files[0])
}, false);

function onSubmit() {
document.getElementById("resultTextarea").value = final;
}
