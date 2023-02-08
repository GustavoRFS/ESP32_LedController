import GitHubApi from "./gitHubApi";
import EspApi from "./espApi";

type updateResponse = {
  body: string;
  assets: {
    name: string;
  }[];
}[];

export const getUpdates = async () => {
  const { data } = await GitHubApi.get<updateResponse>("/releases");
  return data;
};

export const hasUpdates = async () => {
  const { status } = await EspApi.get("/has-updates");

  return status === 200;
};
