package icuInterface;

public class CRCUtil {
	
	// used by IMP731
	
	private static int[] crcTable0c2 = { 0, 145, 97, 240, 194, 83, 163, 50, 199, 86, 166, 55, 5, 148, 100, 245, 205,
			92, 172, 61, 15, 158, 110, 255, 10, 155, 107, 250, 200, 89, 169, 56, 217, 72, 184, 41, 27, 138, 122, 235,
			30, 143, 127, 238, 220, 77, 189, 44, 20, 133, 117, 228, 214, 71, 183, 38, 211, 66, 178, 35, 17, 128, 112,
			225, 241, 96, 144, 1, 51, 162, 82, 195, 54, 167, 87, 198, 244, 101, 149, 4,

			60, 173, 93, 204, 254, 111, 159, 14, 251, 106, 154, 11, 57, 168, 88, 201, 40, 185, 73, 216, 234, 123, 139,
			26, 239, 126, 142, 31, 45, 188, 76, 221, 229, 116, 132, 21, 39, 182, 70, 215, 34, 179, 67, 210, 224, 113,
			129, 16, 161, 48, 192, 81, 99, 242, 2, 147, 102, 247, 7, 150, 164, 53, 197, 84, 108, 253, 13, 156, 174, 63,
			207, 94, 171, 58, 202, 91, 105, 248, 8, 153, 120, 233, 25, 136, 186, 43, 219, 74, 191, 46, 222, 79, 125,
			236, 28, 141, 181, 36, 212, 69, 119, 230, 22, 135, 114, 227, 19, 130, 176, 33, 209, 64, 80, 193, 49, 160,
			146, 3, 243, 98, 151, 6, 246, 103, 85, 196, 52, 165, 157, 12, 252, 109, 95, 206, 62, 175, 90, 203, 59, 170,
			152, 9, 249, 104, 137, 24, 232, 121, 75, 218, 42, 187, 78, 223, 47, 190, 140, 29, 237, 124, 68, 213, 37,
			180, 134, 23, 231, 118, 131, 18, 226, 115, 65, 208, 32, 177 };
	private static int[] CRCTable = { 0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf, 0x8c48, 0x9dc1,
			0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7, 0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7,
			0x643e, 0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876, 0x2102, 0x308b, 0x0210, 0x1399,
			0x6726, 0x76af, 0x4434, 0x55bd, 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5, 0x3183,
			0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c, 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66,
			0xd8fd, 0xc974, 0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb, 0xce4c, 0xdfc5, 0xed5e,
			0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3, 0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
			0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72, 0x6306, 0x728f, 0x4014, 0x519d, 0x2522,
			0x34ab, 0x0630, 0x17b9, 0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1, 0x7387, 0x620e,
			0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x738, 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9,
			0x8b70, 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7, 0x0840, 0x19c9, 0x2b52, 0x3adb,
			0x4e64, 0x5fed, 0x6d76, 0x7cff, 0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036, 0x18c1,
			0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e, 0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7,
			0xc03c, 0xd1b5, 0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd, 0xb58b, 0xa402, 0x9699,
			0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134, 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
			0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a,
			0xb2b3, // 
			0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72,
			0x3efb, //
			0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb,
			0xa232, //
			0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3,
			0x2e7a, // 
			0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238,
			0x93b1, //
			0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9, 0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab,
			0xa022, 0x92b9, 0x8330, 0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0xf78 };

	public static int getCRC16(byte[] list, int start, int end) {
		int CRCval = 0xffff;
		int index;

		// System.out.println();
		for (int i = start; i < end; ++i) {
			int val = list[i];
			if (val < 0)
				val += 256;

			index = val ^ (CRCval & 0x00ff);
			CRCval = (CRCval >> 8) ^ CRCTable[index];

		}

		return CRCval;
	}

	public static int getCRC16Aesculon(byte[] buf, int bufLen, int startCRC) {
		int CRCval = startCRC;

		for (byte b : buf) {
			int val = b;
			if (val < 0)
				val += 256;

			int index = (val ^ CRCval) & 0x00ff;
			//System.out.print( Integer.toHexString(val) );
			// System.out.print( " (" + Integer.toHexString(index) + "," + Integer.toHexString(CRCTable[index]) + ")");
			//System.out.print(" wCRC=" + Integer.toHexString(CRCval) + " --> ");
			CRCval = CRCTable[index] ^ (CRCval >> 8);
			//System.out.println( Integer.toHexString(CRCval) );

			if ((--bufLen) == 0) {
				break;
			}
		}

		return CRCval;
	}

	public static int getCRC16X(int CRCval, byte[] list, int start, int end) {
		int index;

		// System.out.println();
		for (int i = start; i < end; ++i) {
			int val = list[i];
			if (val < 0)
				val += 256;

			index = val ^ (CRCval & 0x00ff);
			CRCval = (CRCval >> 8) ^ CRCTable[index];

			// System.out.format("val=%x CRC=%x\n", val, CRCval );
		}

		return CRCval;
	}

	/*
	 * This is a generator based method that came from the Philips VueLink documentation
	 */
	public static int getCRC16g(byte[] p, int start, int length) {
		int generator_polynom = 0x8810;
		int carry;

		int sum = 0;
		for (int ii = 0; ii < length; ii++) {

			sum ^= p[ii + start] << 8;
			for (int i = 0; i < 8; i++) {
				carry = ((sum & 0x8000) == 0) ? 0 : 1;

				if (carry != 0)
					sum ^= generator_polynom;
				sum = (sum << 1) + carry;
			}
		}
		return sum & 0xffff;
	}

	public static int getCRC16forC2(byte[] s, int len) {
		int crc = 0;

		for (int i = 0; i < len; i++) {
			int ch = s[i];

			if (ch < 0)
				ch += 256;

			int t = ch ^ ((crc & 0xff00) >> 8);
			t = (t >> 4) ^ t;
			t = ((t << 5) ^ t) ^ (crc << 8);
			crc = (t << 12) ^ t;
		}

		return crc & 0xffff;
	}

	public static int getChecksum(byte[] array, int start, int len) {
		int sum = 0;
		for (int i = start; i < len; ++i) {
			int byt = array[i];
			if (byt < 0) {
				byt += 256;
			}
			sum += byt;
		}
		return sum & 0xffff;
	}

	/* CRC-8 Calculation
	   =================

	erstellt von: Kurt Moraw (Juli 2009) www.helitron.de

	Grundlagen zu diesen Funktionen wurden der Webseite:
	http://www.cs.waikato.ac.nz/~312/crc.txt
	entnommen (A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS)

	Das Ergebnis wurde geprueft mit dem CRC-Calculator:
	http://www.zorc.breitbandkatze.de/crc.html

	Das Generator-Polynom wurde wie folgt gewaehlt:
	Polynom = x^8+x^7+x^6+x^4+x^2+1 = x^8+x^7+x^6+x^4+x^2+X^0
	das entspricht: (1) 1101 0101 = Hex d5

	bis zu einer maximalen Bitlaenge von 93 entspricht die Datensicherungsfunktion der Hamming-Distanz 4
	*/

	/* crc8_bytecalc

	diese Funktion enthaelt die CRC8 Schleife fuer 8 Bit einer Nachricht.
	Sie wird solange aufgerufen bis die komplette Nachricht verarbeitet wurde,
	danach muss sie nochmals mit dem Wert 0 aufgerufen werden um die CRC-8 Berechnung abzuschliessen

	Parameter: byte ... ein Byte der Nachricht
	Return: aktueller Wert des CRC-8
	*/

	public static char getCRC8(byte byt, char reg) {
		int i; // Schleifenzaehler
		char flag; // flag um das oberste Bit zu merken
		char polynom = 0xd5; // Generatorpolynom

		// gehe fuer jedes Bit der Nachricht durch
		for (i = 0; i < 8; i++) {
			if ((reg & 0x80) != 0)
				flag = 1;
			else
				flag = 0; // Teste MSB des Registers
			reg <<= 1; // Schiebe Register 1 Bit nach Links und
			if ((byt & 0x80) != 0)
				reg |= 1; // Fülle das LSB mit dem naechsten Bit der Nachricht auf	
			byt <<= 1; // nächstes Bit der Nachricht
			if (flag != 0)
				reg ^= polynom; // falls flag==1, dann XOR mit Polynom
		}
		return reg;
	}

	/* crc8_messagecalc

	Ruft crc8_bytecalc solange auf bis die Nachricht vollstaendig abgearbeitet wurde, danach
	wird crc8_bytecalc noch einmal mit Wert 0 aufgerufen um die CRC-8 Berechnung abzuschliessen

	Parameter: 
	msg ... Bytearray welches die Nachricht enthaelt
	len ... Laenge der Nachricht
	Return: CRC-8 der kompletten Nachricht
	*/

	public static char getCRC8(byte[] msg, int len) {
		int i;
		char reg = 0; // Rechen-Register fuer den CRC Wert mit Initial Value 0
		for (i = 0; i < len; i++) {
			reg = getCRC8(msg[i], reg); // Berechne fuer jeweils 8 Bit der Nachricht
		}
		return getCRC8((byte) 0, reg); // die Berechnung muss um die Bitlaenge des Polynoms mit 0-Wert fortgefuehrt werden
	}

	public static void main(String [] argv) {
		int pos = 0;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				System.out.print(crcTable0c2[pos++]);
				System.out.print(", ");
			}
			System.out.println();
		}
		char crc8; // Ergebnis
		byte[] message = "AB12".getBytes(); // beliebige Nachricht

		crc8 = getCRC8(message, 4);
		System.out.printf("CRC-8 ist %x\n", crc8);
	}

}
