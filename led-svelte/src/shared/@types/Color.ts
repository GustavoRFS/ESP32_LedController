export type Color = {
  r: number;
  g: number;
  b: number;
};

export type Gradient = {
  color: Color;
  percentage: number;
};

export type Favorite = {
  type: "color" | "gradient";
  value: Partial<Color & Gradient[]>;
};
