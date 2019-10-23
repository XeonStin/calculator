namespace WindowsFormsApp1
{
	partial class Form1
	{
		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows 窗体设计器生成的代码

		/// <summary>
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent()
		{
			this.textBoxInput = new System.Windows.Forms.TextBox();
			this.textBoxResult = new System.Windows.Forms.TextBox();
			this.buttonCalculate = new System.Windows.Forms.Button();
			this.labelInput = new System.Windows.Forms.Label();
			this.labelResult = new System.Windows.Forms.Label();
			this.SuspendLayout();
			// 
			// textBoxInput
			// 
			this.textBoxInput.Location = new System.Drawing.Point(103, 21);
			this.textBoxInput.Name = "textBoxInput";
			this.textBoxInput.Size = new System.Drawing.Size(370, 21);
			this.textBoxInput.TabIndex = 0;
			this.textBoxInput.KeyDown += new System.Windows.Forms.KeyEventHandler(this.textBoxInput_KeyDown);
			// 
			// textBoxResult
			// 
			this.textBoxResult.Location = new System.Drawing.Point(103, 62);
			this.textBoxResult.Name = "textBoxResult";
			this.textBoxResult.ReadOnly = true;
			this.textBoxResult.Size = new System.Drawing.Size(251, 21);
			this.textBoxResult.TabIndex = 1;
			// 
			// buttonCalculate
			// 
			this.buttonCalculate.Location = new System.Drawing.Point(375, 62);
			this.buttonCalculate.Name = "buttonCalculate";
			this.buttonCalculate.Size = new System.Drawing.Size(97, 23);
			this.buttonCalculate.TabIndex = 2;
			this.buttonCalculate.Text = "计算 (Enter)";
			this.buttonCalculate.UseVisualStyleBackColor = true;
			this.buttonCalculate.Click += new System.EventHandler(this.buttonCalculate_Click);
			// 
			// labelInput
			// 
			this.labelInput.AutoSize = true;
			this.labelInput.Location = new System.Drawing.Point(17, 24);
			this.labelInput.Name = "labelInput";
			this.labelInput.Size = new System.Drawing.Size(77, 12);
			this.labelInput.TabIndex = 4;
			this.labelInput.Text = "输入表达式：";
			// 
			// labelResult
			// 
			this.labelResult.AutoSize = true;
			this.labelResult.Location = new System.Drawing.Point(17, 65);
			this.labelResult.Name = "labelResult";
			this.labelResult.Size = new System.Drawing.Size(65, 12);
			this.labelResult.TabIndex = 5;
			this.labelResult.Text = "计算结果：";
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(514, 112);
			this.Controls.Add(this.labelResult);
			this.Controls.Add(this.labelInput);
			this.Controls.Add(this.buttonCalculate);
			this.Controls.Add(this.textBoxResult);
			this.Controls.Add(this.textBoxInput);
			this.Name = "Form1";
			this.Text = "表达式求值 by Xeon Stin";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox textBoxInput;
		private System.Windows.Forms.TextBox textBoxResult;
		private System.Windows.Forms.Button buttonCalculate;
		private System.Windows.Forms.Label labelInput;
		private System.Windows.Forms.Label labelResult;
	}
}

