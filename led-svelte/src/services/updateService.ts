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
  try {
    await EspApi.get("/has-updates");
  } catch (error) {
    return false;
  }

  return true;
};

export const startUpdate = async () => {
  try {
    await EspApi.post("/update");
  } catch (error) {
    return false;
  }

  return true;
};
