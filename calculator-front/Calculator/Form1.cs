using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
	public partial class Form1 : Form
	{
		public Form1()
		{
			InitializeComponent();
		}

		private void getResult()
		{
			string exePath = System.Environment.CurrentDirectory + "\\calculator-end.exe";
			string processedInput = textBoxInput.Text.Replace(" ", "");

			textBoxResult.Text = RunExeByProcess(exePath, processedInput);
		}

		private void buttonCalculate_Click(object sender, EventArgs e)
		{
			getResult();
		}

		public static string RunExeByProcess(string exePath, string argument)
		{
			//开启新线程
			System.Diagnostics.Process process = new System.Diagnostics.Process();
			//调用的exe的名称
			process.StartInfo.FileName = exePath;
			//传递进exe的参数
			process.StartInfo.Arguments = argument;
			process.StartInfo.UseShellExecute = false;
			//不显示exe的界面
			process.StartInfo.CreateNoWindow = true;
			process.StartInfo.RedirectStandardOutput = true;
			process.StartInfo.RedirectStandardInput = true;
			process.Start();

			process.StandardInput.AutoFlush = true;

			string result = null;
			while (!process.StandardOutput.EndOfStream)
			{
				result += process.StandardOutput.ReadLine() + Environment.NewLine;
			}
			process.WaitForExit();
			return result;
		}

		private void textBoxInput_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyValue == (char)13)
			{
				getResult();
			}
		}
	}
}
