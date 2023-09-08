
Video capture: Open Broadcast Studio
Video editor: Openshot-qt

Exported data with the following settings:
	HDV 720 24p
	-- adjusted for
		0.384 Mb video rate
		20 frames/sec
		stereo - 192kb

Post processing required to normalize sound:

ffmpeg -i demo-2.mp4 -af "volume=5dB" -c:v copy -c:a aac -strict experimental -b:a 192k output.mp4

See notes in Rubal book on Dec 11.

